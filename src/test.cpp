#include "constants.hpp"
#include "snake_map.hpp"
#include "snake.hpp"
#include <cstdio>
#include <ncurses.h>


int main() {
	initscr();
	SnakeMap snake_map;
	snake_map.draw();
	Snake snake;
	snake.initialize();
	snake.draw();
	refresh();
	getch();
	endwin();
	return 0;
}