#ifndef OS_DEPENDENT_H
#define OS_DEPENDENT_H

#include <utility>

namespace os {
	void draw_char(std::pair<unsigned, unsigned> coords, char ch);
	void draw_string(std::pair<unsigned, unsigned> coords, const char* str);
	void clear_line(std::pair<unsigned, unsigned> coords);
	void refresh_screen();
	void sleep(int milliseconds);
	void initialize_screen();
	void block_getch();
	void unblock_getch();
}

#endif