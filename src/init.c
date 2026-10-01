#include <unistd.h>
#include <stddef.h>

#include <curses.h>

void init(void) {
    initscr();
    
    addch(0x0F00 | 'W');
    addch(0x0F00 | 'e');
    addch(0x0F00 | 'l');
    addch(0x0F00 | 'c');
    addch(0x0F00 | 'o');
    addch(0x0F00 | 'm');
    addch(0x0F00 | 'e');
    addch(0x0F00 | ' ');
    addch(0x0F00 | 't');
    addch(0x0F00 | 'o');
    addch(0x0F00 | ' ');
    addch(0x0F00 | 'E');
    addch(0x0F00 | 'D');
    addch(0x0F00 | 'D');
    addch(0x0F00 | 'I');
    addch(0x0F00 | 'E');
    addch(0x0F00 | 'O');
    addch(0x0F00 | 'S');
    addch(0x0F00 | '.');    
}
