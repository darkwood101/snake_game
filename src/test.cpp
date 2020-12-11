#include "constants.hpp"
#include "snake_map.hpp"
#include "snake.hpp"
#include <cstdio>
#include <ncurses.h>
#include <unistd.h>
#include <thread>


int main() {
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	Snake snake;
	Food food;
	SnakeMap snake_map(&snake, &food);
	snake_map.wait_input();
	snake_map.draw();
	while (true) {
		//snake_map.generate_food()
		snake_map.move_snake();
		usleep(500000);
	}
	endwin();
	return 0;
}