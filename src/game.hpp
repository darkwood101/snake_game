/*
This is the header files where the class Game is declared. This is the core class of the game,
as it controls the flow and the dynamic of the entire game. It contains pointers to instances of Snake, Food, Border, and Text.
It also contains a lot of helper methods for controlling the game flow.
*/

#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "food.hpp"
#include "border.hpp"
#include "text.hpp"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;       // Used to measure the delay.

class Game {

private:
    std::chrono::time_point<Clock> beginTime_;          // The beginning time of a frame.
    std::chrono::time_point<Clock> endTime_;            // The ending time of a frame.
    std::chrono::microseconds duration_;                // The duration of the frame in microseconds.
    std::chrono::microseconds delay_;                   // The delay between frames in microseconds.
    std::chrono::microseconds delayDecrement_;          // The step in which to decrement the delay.
    std::chrono::microseconds minDelay_;                // The minimum possible delay.
    size_t screenWidth_;                                // The width of the screen in pixels.
    size_t screenHeight_;                               // The height of the screen in pixels.
    SDL_Window* mainWindow_;                            // Pointer to the game window.
    SDL_Renderer* renderer_;                            // Pointer to the renderer.
    SDL_Event event_;                                   // Used to detect events.
    Snake* snake_;                                      // Pointer to instance of Snake.
    Food* food_;                                        // Pointer to instance of Food,
    Border* border_;                                    // Pointer to instance of Border.
    Text* text_;                                        // Pointer to instance of Text.
    char message_[100];                                 // The char array used to store messages to be displayed on the screen.
    size_t score_;                                      // Player's score.
    bool grow_;                                         // True if the snake is supposed to grow.

public:
    Game();                                             // Constructor
    ~Game();                                            // Destructor.
    void init();                                        // Initializes SDL-related objects.
    int startScreen();                                  // Starts the game and display the starting screen.
    int run();                                          // Runs the game.
    void render();                                      // Renders all objects on the screen.
    int update();                                       // Updates the state of the game.
    int processInput();                                 // Processes the user's input.
    void gameOverScreen();                              // Displays the game over screen when the snake dies.
    void updateDelay();                                 // Updates the delay between frames.

    bool isBlank(std::pair<unsigned, unsigned> coords); // Returns true if the cell at `coords` is blank.
    int moveSnake();                                    // Moves snake by one cell.
    bool isDead();                                      // Checks whether the snake is dead.
    bool ateFood();                                     // Checks whether the snake hit the food.
};


#endif