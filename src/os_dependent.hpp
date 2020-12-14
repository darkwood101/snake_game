/*
This header file contains declarations of all functions that are OS-dependent. They are all in the `os`
namespace. For Linux specifically, all these functions use the <ncurses> library, or the header
<unistdh.h>. Separating these functions is meant to enable easier porting to other operating systems.
*/

#ifndef OS_DEPENDENT_H
#define OS_DEPENDENT_H

#include <utility>

namespace os {
    void draw_char(std::pair<unsigned, unsigned> coords, char ch);              // Draw the specified character at `coords`
    void draw_string(std::pair<unsigned, unsigned> coords, const char* str);    // Draw the specified string at `coords`.
    void clear_line(std::pair<unsigned, unsigned> coords);                      // Clear screen until the end of line, starting at `coords`.
    void refresh_screen();                                                      // Refresh the screen.
    void sleep(int milliseconds);                                               // Sleep for a given amount of milliseconds.
    void initialize_screen();                                                   // Initialize the state of the screen for the game.
    void block_getch();                                                         // Make getch blocking.
    void unblock_getch();                                                       // Make getch non-blocking.
}

#endif