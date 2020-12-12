#include "game.hpp"

#include <utility>
#include <atomic>
#include <ncurses.h>
#include <cstring>
#include <time.h>
#include <cstdlib>
#include <unistd.h>


// Game::Game(snake, food)
//		Initializes the instance of Game with pointers to Snake and Food objects.
//		Sets the initial values of game_over and score.

Game::Game(Snake* snake, Food* food) {
	snake_ = snake;
	food_ = food;
	game_over = false;
	score = 0;
	delay = init_delay;
}


// Game::run()
//		Sets the initial state of the screen and runs the game.
//		This function is called from main.

void Game::run() {
	initscr();				// Initialize the screen in ncurses mode.
	clear();				// Clear the screen.
	noecho();				// Disables echo from getch.
	cbreak();				// Disable line buffering.
	curs_set(0);			// Makes the cursor invisible.
	wait_input();			// Detaches a thread to wait for input.
	generate_food();		// Initial food generation.
	draw_world();			// Initial draw of the map.
	print_instructions();	// Print movement instructions.
	print_score();			// Print player's score.
	// Loop moving the snake. If <0 is returned, game over.
	// There is a microsleep after each iteration.
	while (true) {
		if (move_snake() < 0) {
			mvprintw(map_height, 0, "Game over. Your score is %d. \n \nPress q to exit...", score);
			move(map_height + 3, 0);
			clrtoeol();	// Clear the score message.
			refresh();
			th.join();	// Wait for the input thread to finish.
			endwin();
			return;
		}
		print_score();
		draw_world();
		usleep(delay * milliseconds);
	}
}


// Game::draw_world()
//		Draws the state of the map. For each character, it's checked whether
//		it's snake head, snake body, border, food, or blank.

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


// Game::generate_food()
//		Generates food on a new position. The new position must be blank. The function
//		Food::get_food_pos() is called in a loop until the appropriate food position is found.

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


// Game::cell_is_blank(coords)
//		Returns true if the cell at coordinates `coords` is blank, false otherwise.

bool Game::cell_is_blank(std::pair<unsigned, unsigned> coords) {
	unsigned y = coords.first;
	unsigned x = coords.second;
	return !((x == 0) || (x == map_width - 1) || (y == 0) || (y == map_height - 1) || (snake_->is_in_snake(coords)));
}


// Game::input_thread()
//		This function runs on a separate thread from the main thread. It blocks on the getch() call waiting for user input.
//		Once the user input is obtained, the direction of the snake is updated accordingly.

void Game::input_thread() {
	
	while (true) {
		char ch = getch();
		while (game_over) {
			if (ch == 'q') {
				return;
			}
			ch = getch();
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


// Game::wait_input()
//		A wrapper for Game::input_thread. It runs Game::input_thread in a separate thread.

void Game::wait_input() {
	th = std::thread(&Game::input_thread, this);
}


// Game::move_snake()
//		Controls a solid portion of the game dynamic.
//		Checks whether the snake hit the food.
//		Reduces delay accordingly.
//		It moves the snake, and checks whether it's dead.
//		If dead, returns -1. If not dead, draws the map and returns 0.

int Game::move_snake() {
	bool grow = ate_food();
	snake_->move(grow);
	if (grow) {
		++score;
		if ((score % 10 == 0) && (delay > min_delay)) {
			delay -= delay_decrement;
		}
		generate_food();
	}
	if (is_dead()) {
		game_over = true;
		return -1;
	}
	return 0;
}


// Game::is_dead()
//		Returns true if the snake hit a wall or itself.
//		This is equivalent to checking whether the snake head is in a blank cell or not.

bool Game::is_dead() {
	return !(cell_is_blank(snake_->get_head()));
}


// Game::ate_food()
//		Returns true if the snake hit food.
//		This is equivalent to checking if snake head coordinates are equal to food coordinates.

bool Game::ate_food() {
	return snake_->get_head() == food_->get_food_pos();
}


// Game::print_instructions()
//		Prints movement instructions at the beginning of the game.

void Game::print_instructions() {
	mvprintw(map_height, 0, "Use W, A, S, D to move.");
	refresh();
}


// Game::print_score()
//		Prints the player score.

void Game::print_score() {
	mvprintw(map_height + 2, 0, "Score: %d\n", score);
}