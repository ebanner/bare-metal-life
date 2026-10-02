#include <unistd.h>
#include <stddef.h>

#include <curses.h>

void init(void) {
    initscr();

    addstr("Welcome to EDDIEOS.");  
}
