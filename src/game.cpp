#include "game.hpp"
#include "globals.hpp"

#include <thread>


// Game::Game()
//      Initializes the instance of Game with pointers to Snake, Food, Border, and Text.
//      Initializes the SDL-related objects.
//      Initializes other members of the Game class.

Game::Game() {
    screenWidth_ = globals::mapWidth;
    screenHeight_ = globals::mapHeight + 100;
    mainWindow_ = nullptr;
    renderer_ = nullptr;
    delay_ = std::chrono::microseconds(110000);
    minDelay_ = std::chrono::microseconds(60000);
    delayDecrement_ = std::chrono::microseconds(10000);
    score_ = 0;
    grow_ = false;
    init();
    snake_ = new Snake(renderer_);
    food_ = new Food(renderer_);
    border_ = new Border(renderer_);
    text_ = new Text(renderer_);
}


// Game::~Game()
//      Destructor for the Game class. Deletes dynamically allocated objects.
//      Cleans up SDL-related objects.

Game::~Game() {
    delete snake_;
    delete food_;
    delete border_;
    delete text_;
    SDL_DestroyWindow(mainWindow_);
    SDL_DestroyRenderer(renderer_);
    SDL_FreeSurface(icon_);
    TTF_Quit();
    SDL_Quit();
}


// Game::init()
//      Initializes SDL and TTF. After each step, it is checked whether SDL returned an error.
//      If so, SDLError() is called, which prints the error to stderr and exits.
//      Sets the default rendering color to black.

void Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) globals::SDLError();
    if (TTF_Init() < 0) globals::SDLError();
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) globals::SDLError();
    mainWindow_ = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth_, screenHeight_, SDL_WINDOW_SHOWN);
    if (mainWindow_ == nullptr) globals::SDLError();
    renderer_ = SDL_CreateRenderer(mainWindow_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) globals::SDLError();
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    icon_ = SDL_LoadBMP("res/icon.bmp");
    if (icon_ == nullptr) globals::SDLError();
    SDL_SetWindowIcon(mainWindow_, icon_);
}


// Game::startScreen()
//      Generates the food.
//      Renders all objects.
//      Displays the appropriate messages for the starting screen.
//      Waits for the user's input.

int Game::startScreen() {
    food_->generate(snake_);
    SDL_RenderClear(renderer_);
    sprintf(message_, "Use W, A, S, D to move the snake.");
    text_->update(message_);
    text_->render(20, globals::mapHeight + 10);
    sprintf(message_, "Press SPACE to start, Q to quit.");
    text_->update(message_);
    text_->render(20, globals::mapHeight + 50);
    snake_->render();
    food_->render();
    border_->render();
    SDL_RenderPresent(renderer_);

    while (SDL_WaitEvent(&event_)) {
        if (event_.type == SDL_KEYDOWN) {
            SDL_Keycode key = event_.key.keysym.sym;
            switch (key) {
                case SDLK_SPACE:
                    return globals::gameStart;

                case SDLK_q:
                    return globals::userExit;

                default:
                    break;
            }
        }

        else if (event_.type == SDL_QUIT) {
            return globals::userExit;
        }
    }

    return globals::gameStart;
}


// Game::run()
//      Runs the game.
//      This function controls the state of the game.
//      Returns globals::userExit if the user pressed q or closed the window,
//      and returns globals::playerDead if the player died.

int Game::run() {
    sprintf(message_, "Score: %lu\n", score_);
    text_->update(message_); 
    while (true) {
        // Begin measuring the time for the frame.
        beginTime_ = std::chrono::high_resolution_clock::now();
        // Update the game state.
        int gameStatus = update();
        // If user exited or the player died, return to main.
        if ((gameStatus == globals::userExit) || (gameStatus == globals::playerDead)) return gameStatus;
        // Render everything,
        render();
        // Stop measuring the time for the frame.
        endTime_ = std::chrono::high_resolution_clock::now();
        // If the duration of the frame was less than the required delay, sleep to make up for the difference.
        duration_ = std::chrono::duration_cast<std::chrono::microseconds>(endTime_ - beginTime_);
        if (duration_ < delay_) {
            std::this_thread::sleep_for(delay_ - duration_);
        }
    }
}


// Game::render()
//      Draws everything on the screen.

void Game::render() {
    SDL_RenderClear(renderer_);
    snake_->render();
    food_->render();
    border_->render();
    text_->render(20, globals::mapHeight + 20);
    SDL_RenderPresent(renderer_);
}


// Game::update()
//      Controls the dynamics of the game.
//      Processes user's input and checks whether the user exited.
//      Moves the snake.
//      Checks whether the snake is dead.
//      Checks whether the snake is supposed to grow. If not,
//      it erases the snake's tail (this equivalent to moving the snake's tail).
//      Checks whether the snake hit the food. If yes, updates the score and the message.

int Game::update() {
    if (processInput() == globals::userExit) return globals::userExit;
    
    snake_->advance();
    if (isDead()) {
        return globals::playerDead;
    }
    if (!grow_) {
        snake_->clearTail();
    }
    grow_ = ateFood();
    if (grow_) {
        ++score_;
        sprintf(message_, "Score: %lu\n", score_);
        text_->update(message_);
        food_->generate(snake_);
        updateDelay();
    }

    return globals::gameContinue;
}


// Game::gameOverScreen()
//      Erases the snake and leaves just the black board with the borders/
//      Prints the game over messages.
//      Waits until the user presses q.

void Game::gameOverScreen() {
    SDL_RenderClear(renderer_);
    sprintf(message_, "Game over. Your score was %lu.", score_);
    text_->update(message_);
    text_->render(20, globals::mapHeight + 10);
    sprintf(message_, "Press Q to quit.");
    text_->update(message_);
    text_->render(20, globals::mapHeight + 50);
    border_->render();
    SDL_RenderPresent(renderer_);
    while (SDL_WaitEvent(&event_)) {
        if (event_.type == SDL_KEYDOWN) {
            SDL_Keycode key = event_.key.keysym.sym;
            switch (key) {
                case SDLK_q:
                    return;

                default:
                    break;
            }
        }
        else if (event_.type == SDL_QUIT) {
            return;
        }
    }
}


// Game::isBlank(coords)
//      Returns true if the cell at coordinates `coords` is blank, false otherwise.

bool Game::isBlank(std::pair<unsigned, unsigned> coords) {
    unsigned y = coords.first;
    unsigned x = coords.second;
    return !((x == 0) || (x == globals::mapWidth - globals::unitLength) || (y == 0) || (y == globals::mapHeight - globals::unitLength) || (snake_->isInSnake(coords)));
}


// Game::processInput()
//      Processes any input obtained from the user. It's called after each microsleep (millisleep hehe)
//      and it harvests all the input that was sent by the user during the sleep. All those requests for new directions
//      are then added to the deque Snake::newDirections_ (with some exceptions), which is handled by Snake::setDirection.
//      If q is pressed or the windows is closed, returns globals::userExit.

int Game::processInput() {
    while (SDL_PollEvent(&event_)) {
        if (event_.type == SDL_KEYDOWN) {
            SDL_Keycode key = event_.key.keysym.sym;
            switch(key) {
                case SDLK_w: {
                    snake_->setDirection(snake_->up);
                    break;
                }
                case SDLK_s: {
                    snake_->setDirection(snake_->down);
                    break;
                }
                case SDLK_a: {
                    snake_->setDirection(snake_->left);
                    break;
                }
                case SDLK_d: {
                    snake_->setDirection(snake_->right);
                    break;
                }
                case SDLK_q: {
                    return globals::userExit;
                }
            }
        }
        else if (event_.type == SDL_QUIT) {
            return globals::userExit;
        }
    }

    return globals::gameContinue;
}


// Game::isDead()
//      Returns true if the snake hit a wall or itself.
//      This is equivalent to checking whether the snake head is in a blank cell or not.

bool Game::isDead() {
    if ((!grow_) && (snake_->getHead() == snake_->getTail())) {
        return false;
    }
    return !(isBlank(snake_->getHead()));
}


// Game::ateFood()
//      Returns true if the snake hit food.
//      This is equivalent to checking if snake head coordinates are equal to food coordinates.

bool Game::ateFood() {
    return snake_->getHead() == food_->getFoodPos();
}


// Game::updateDelay()
//      Updates the delay between frames. The update happens only if the score is a multiple of 10.

void Game::updateDelay() {
    if ((score_ % 10 == 0) && (delay_ > minDelay_)) delay_ -= delayDecrement_;
}