#include "os_dependent.hpp"
#include <ncurses.h>
#include <unistd.h>

namespace os {
	void draw_char(std::pair<unsigned, unsigned> coords, char ch) {
		unsigned y = coords.first;
		unsigned x = coords.second;
		mvprintw(y, x, "%c", ch);
	}


	void draw_string(std::pair<unsigned, unsigned> coords, const char* str) {
		unsigned y = coords.first;
		unsigned x = coords.second;
		mvprintw(y, x, str);
	}


	void clear_line(std::pair<unsigned, unsigned> coords) {
		unsigned y = coords.first;
		unsigned x = coords.second;
		move(y, x);
		clrtoeol();
	}


	void refresh_screen() {
		refresh();
	}


	void sleep(int milliseconds) {
		usleep(milliseconds * 1000);
	}


	void initialize_screen() {
	    initscr();              // Initialize the screen in ncurses mode.
	    clear();                // Clear the screen.
	    noecho();               // Disables echo from getch.
	    cbreak();               // Disable line buffering.
	    curs_set(0);            // Makes the cursor invisible.
	    os::unblock_getch();
	}


	void block_getch() {
		nodelay(stdscr, false);
	}


	void unblock_getch() {
		nodelay(stdscr, true);
	}
}