#include "game.hpp"

#include <utility>
#include <atomic>
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <thread>
#include <unistd.h>

Game::Game(Snake* snake, Food* food) {
	snake_ = snake;
	food_ = food;
	game_over = false;
}

void Game::run() {
	initscr();
	clear();
	noecho();
	cbreak();
	curs_set(0);
	wait_input();
	generate_food();
	draw_world();
	while (true) {
		if (move_snake() < 0) {
			mvprintw(map_height, 0, "GAME OVER \nPress any key to exit...");
			refresh();
			getch();
			endwin();
			return;
		}
		usleep(200000);
	}
}

void Game::draw_world() {
	for (unsigned y = 0; y != map_height; ++y) {
		for (unsigned x = 0; x != map_width; ++x) {
			std::pair<unsigned, unsigned> coords = std::make_pair(y, x);
			if (snake_->is_snake_head(coords)) {
				mvprintw(y, x, snake_head_);
			}
			else if (snake_->is_in_snake(coords)) {
					mvprintw(y, x, snake_char_);
			}
			else if (coords == food_->get_food_pos()) {
				mvprintw(y, x, food_char_);
			}
			else if (x == 0 || x == map_width - 1 || y == 0 || y == map_height - 1) {
				mvprintw(y, x, border_char_);
			}
			else {
				mvprintw(y, x, blank_char_);
			}
		}
	}

	refresh();
}


void Game::generate_food() {
	std::pair<unsigned, unsigned> current_food_pos = food_->get_food_pos();
	unsigned y = current_food_pos.first;
	unsigned x = current_food_pos.second;
	mvprintw(y, x, blank_char_);
	do {
		food_->generate();
	}
	while (!(cell_is_blank(food_->get_food_pos())));

}


bool Game::cell_is_blank(std::pair<unsigned, unsigned> coords) {
	unsigned y = coords.first;
	unsigned x = coords.second;
	return !((x == 0) || (x == map_width - 1) || (y == 0) || (y == map_height - 1) || (snake_->is_in_snake(coords)));
}

//threading
void Game::input_thread() {
	
	while (true) {
		char ch = getch();
		if (game_over) {
			endwin();
			exit(0);
		}
		snake_->direction_mutex.lock();
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

		snake_->direction_mutex.unlock();
	}
}

void Game::wait_input() {
	std::thread th(&Game::input_thread, this);
	th.detach();
}

int Game::move_snake() {
	bool grow = ate_food();
	snake_->move(grow);
	if (grow) {
		generate_food();
	}
	if (is_dead()) {
		game_over = true;
		return -1;
	}
	draw_world();
	return 0;
}

bool Game::is_dead() {
	return !(cell_is_blank(snake_->get_head()));
}

bool Game::ate_food() {
	return snake_->get_head() == food_->get_food_pos();
}