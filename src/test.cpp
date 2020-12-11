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
		if (snake_map.move_snake() < 0) {
			mvprintw(constants::map_height, 0, "GAME OVER \n Press any key to exit...");
			refresh();
			getch();
			endwin();
			exit(0);
		}
		usleep(200000);
	}
	endwin();
	return 0;
}