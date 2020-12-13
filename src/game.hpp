#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "food.hpp"


class Game {

private:
    // The snake and food objects.
    Snake* snake_;
    Food* food_;
    // Characters for representing different objects on the map.
    const char border_char_ = 'o';
    const char blank_char_ = ' ';
    const char food_char_ = '$';
    const char snake_char_ = 'x';
    const char snake_head_ = 'o';
    bool game_over;                                             // True if game is over.
    unsigned score;                                             // Player's score.
    unsigned delay;                                             // The sleeping delay.
    static constexpr unsigned min_delay = 80;                   // Minimum delay in milliseconds.
    static constexpr unsigned init_delay = 200;                 // Initial delay in milliseconds.
    static constexpr unsigned delay_decrement = 20;             // Delay decrement in milliseconds.

public:
    Game(Snake* snake, Food* food);                             // Constructor, initializes some values.
    void run();                                                 // Start the game.
    void draw_borders();                                        // Draws the borders of the map.
    void draw_snake();                                          // Draws the snake.
    void draw_food();                                           // Draws the food.
    void generate_food();                                       // Generates food at appropriate position.
    bool cell_is_blank(std::pair<unsigned, unsigned> coords);   // Returns true if the cell at coords is blank.
    void process_input();                                       // Process the user's input.
    int move_snake();                                           // Moves snake by one cell. Returns -1 if the snake dies.
    bool is_dead();                                             // Checks whether the snake is dead.
    bool ate_food();                                            // Checks whether the snake hit the food.
    void print_instructions();                                  // Prints movement instructions.
    void print_score();                                         // Prints the player score.
    // The height and width of the map.
    static constexpr unsigned map_height = 20;
    static constexpr unsigned map_width = 50;
};


#endif