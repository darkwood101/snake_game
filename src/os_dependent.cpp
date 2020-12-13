#include "os_dependent.hpp"
#include <ncurses.h>

namespace os {
	void draw_char(std::pair<unsigned, unsigned> coords, char ch) {
		unsigned y = coords.first;
		unsigned x = coords.second;
		mvprintw(y, x, "%c", ch);
	}

	void refresh_screen() {
		refresh();
	}
}