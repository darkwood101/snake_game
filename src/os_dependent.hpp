#ifndef OS_DEPENDENT_H
#define OS_DEPENDENT_H

#include <utility>

namespace os {
	void draw_char(std::pair<unsigned, unsigned> coords, char ch);
	void refresh_screen();
}

#endif