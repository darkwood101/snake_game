#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "food.hpp"
#include <thread>


class Game {

private:
	// The snake and food objects.
	Snake* snake_;
	Food* food_;
	// Characters for representing different objects on the map.
	const char* border_char_ = "o";
	const char* blank_char_ = " ";
	const char* food_char_ = "$";
	const char* snake_char_ = "x";
	const char* snake_head_ = "o";
	bool game_over;												// True if game is over.
	unsigned score;												// Player's score.
	unsigned delay;												// The sleeping delay.
	static constexpr unsigned milliseconds = 1000;				// How many milliseconds in a second.
	static constexpr unsigned min_delay = 80;					// Minimum delay in milliseconds.
	static constexpr unsigned init_delay = 200;					// Initial delay in milliseconds.
	static constexpr unsigned delay_decrement = 20;				// Delay decrement.
	std::thread th;												// Thread which will wait for user input.

public:
	Game(Snake* snake, Food* food);								// Constructor, initializes some values.
	void run();													// Start the game.
	void draw_world();											// Draws the state of the map.
	void generate_food();										// Generates food at appropriate position.
	bool cell_is_blank(std::pair<unsigned, unsigned> coords);	// Returns true if the cell at coords is blank.
	void input_thread();										// A function that runs in a separate thread and waits for input.
	void wait_input();											// Wrapper around input_thread.
	int move_snake();											// Moves snake by one cell. Returns -1 if the snake dies.
	bool is_dead();												// Checks whether the snake is dead.
	bool ate_food();											// Checks whether the snake hit the food.
	void print_instructions();									// Prints movement instructions.
	void print_score();											// Prints the player score.
	// The height and width of the map.
	static const unsigned map_height = 20;
	static const unsigned map_width = 50;
};


#endif