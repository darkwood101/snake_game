#include "game.hpp"
#include "os_dependent.hpp"

#include <utility>
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <unistd.h>


// Game::Game(snake, food)
//      Initializes the instance of Game with pointers to Snake and Food objects.
//      Initializes the screen, and draws the initial state of the world.

Game::Game(Snake* snake, Food* food) {
    snake_ = snake;
    food_ = food;
    score = 0;
    delay = init_delay;
    os::initialize_screen();  // Initialize the screen.
    generate_food();          // Initial food generation.
    draw_borders();           // Draw the borders of the map.
    draw_snake();             // Draw the initial position of the snake.
    draw_food();              // Draw the initial position of the food.
    print_instructions();     // Print the instructions for the user.
    print_score();            // Print the score.
    os::refresh_screen();     // Refresh the screen.
}


// Game::run()
//      Runs the game.
//      This function is called from main.
//      NOTE: to reduce the amount of unnecessary refreshes, only Game::run (except the constructor) should call
//      os::refresh_screen()!!!

void Game::run() {
    // Loop moving the snake. If <0 is returned, game over.
    // There is a microsleep after each iteration.
    while (true) {
        process_input();
        if (move_snake() < 0) {
            char message[100];
            sprintf(message, "Game over. Your score is %d. \n \nPress q to exit...", score);
            os::draw_string(std::make_pair(map_height, 0), message);
            os::clear_line(std::make_pair(map_height + 3, 0));
            os::refresh_screen();
            os::block_getch();     // Make getch blocking again.
            // Wait until user presses q.
            while (true) {
                char ch = getch();
                if (ch == 'q') {
                    break;
                }
            }
            endwin();
            return;
        }
        print_score();
        os::refresh_screen();
        os::sleep(delay);
    }
}


// Game::draw_world()
//      Draws the borders of the map.

void Game::draw_borders() {
    for (unsigned y = 0; y < map_height; ++y) {
        for (unsigned x = 0; x < map_width; x += map_width - 1) {
            os::draw_char(std::make_pair(y, x), border_char_);
        }
    }

    for (unsigned y = 0; y < map_height; y += map_height - 1) {
        for (unsigned x = 1; x < map_width - 1; ++x) {
            os::draw_char(std::make_pair(y, x), border_char_);
        }
    }
}


// Game::draw_food()
//      Draws the food.

void Game::draw_food() {
    os::draw_char(food_->get_food_pos(), food_char_);
}


// Game::draw_snake()
//      Draw the snake.

void Game::draw_snake() {
    std::vector<std::pair<unsigned, unsigned>> snake_pos = snake_->get_snake_pos();
    for (size_t i = 0; i != snake_pos.size() - 1; ++i) {
        os::draw_char(snake_pos[i], snake_char_);
    }
    os::draw_char(snake_pos[snake_pos.size() - 1], snake_head_);
}


// Game::generate_food()
//      Generates food on a new position. The new position must be blank. The function
//      Food::get_food_pos() is called in a loop until the appropriate food position is found.

void Game::generate_food() {
    do {
        food_->generate();  
    }
    while (!(cell_is_blank(food_->get_food_pos())));
}


// Game::cell_is_blank(coords)
//      Returns true if the cell at coordinates `coords` is blank, false otherwise.

bool Game::cell_is_blank(std::pair<unsigned, unsigned> coords) {
    unsigned y = coords.first;
    unsigned x = coords.second;
    return !((x == 0) || (x == map_width - 1) || (y == 0) || (y == map_height - 1) || (snake_->is_in_snake(coords)));
}


// Game::process_input()
//      Processes any input obtained from the user. It's called after each microsleep (millisleep hehe)
//      and it harvests all the input that was sent by the user during the sleep. All those requests for new directions
//      are then added to the deque Snake::new_directions_ (with some exceptions), which is handled by Snake::set_direction.

void Game::process_input() {
    
    while (true) {
        char ch = getch();
        if (ch == ERR) {
            return;
        }
        switch(ch) {
            case 'w': {
                snake_->set_direction(snake_->up);
                break;
            }
            case 's': {
                snake_->set_direction(snake_->down);
                break;
            }
            case 'a': {
                snake_->set_direction(snake_->left);
                break;
            }
            case 'd': {
                snake_->set_direction(snake_->right);
            }
        }
    }
}


// Game::move_snake()
//      Controls a solid portion of the game dynamic.
//      Advances the snake's head.
//      Checks whether the snake hit the food.
//      Checks whether the snake is dead. Returns -1 if the snake is dead, 0 otherwise.
//      If the snake didn't hit food, it clears the tail of the snake.
//      If the snake did hit food. it updates score and appropriately reduces the microsleep length.

int Game::move_snake() {
    snake_->advance();
    bool grow = ate_food();
    if (is_dead(grow)) {
        return -1;
    }
    if (!grow) {
        snake_->clear_tail(blank_char_);
    }
    else {
        ++score;
        if ((score % 10 == 0) && (delay > min_delay)) {
            delay -= delay_decrement;
        }
        generate_food();
        draw_food();
    }
    draw_snake();
    return 0;
}


// Game::is_dead()
//      Returns true if the snake hit a wall or itself.
//      This is equivalent to checking whether the snake head is in a blank cell or not.
//      One exception is the snake hitting its own tail. In that case, if the snake didn't eat any food
//      (i.e. grow is false), the snake shouldn't die.

bool Game::is_dead(bool grow) {
    if ((!grow) && (snake_->get_head() == snake_->get_tail())) {
        return false;
    }
    return !(cell_is_blank(snake_->get_head()));
}


// Game::ate_food()
//      Returns true if the snake hit food.
//      This is equivalent to checking if snake head coordinates are equal to food coordinates.

bool Game::ate_food() {
    return snake_->get_head() == food_->get_food_pos();
}


// Game::print_instructions()
//      Prints movement instructions at the beginning of the game.

void Game::print_instructions() {
    os::draw_string(std::make_pair(map_height, 0), "Use W, A, S, D to move.");
}


// Game::print_score()
//      Prints the player score.

void Game::print_score() {
    char message[100];
    sprintf(message, "Score: %d\n", score);
    os::draw_string(std::make_pair(map_height + 2, 0), message);
}