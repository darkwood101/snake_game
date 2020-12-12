#ifndef GAME_H
#define GAME_H

#include "snake.hpp"
#include "food.hpp"


class Game {

private:
	Snake* snake_;
	Food* food_;
	const char* border_char_ = "o";
	const char* blank_char_ = " ";
	const char* food_char_ = "$";
	const char* snake_char_ = "x";
	const char* snake_head_ = "o";
	const unsigned map_height = 20;
	const unsigned map_width = 50;
	bool game_over;

public:
	Game(Snake* snake, Food* food);
	void run();
	void draw_world();
	void generate_food();
	bool cell_is_blank(std::pair<unsigned, unsigned> coords);
	void input_thread();
	void wait_input();
	int move_snake();
	bool is_dead();
	bool ate_food();
};


#endif