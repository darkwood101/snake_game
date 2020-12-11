#include "constants.hpp"
#include "snake_map.hpp"
#include "snake.hpp"
#include <cstdio>
#include <ncurses.h>
#include <unistd.h>


int main() {
	initscr();
	curs_set(0);
	Snake snake;
	Food food;
	SnakeMap snake_map(&snake, &food);
	snake_map.draw();
	snake.draw();
	refresh();
	while (true) {
		snake_map.generate_food();
		food.print();
		usleep(500000);
	}
	endwin();
	return 0;
}