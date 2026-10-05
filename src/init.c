#include <unistd.h>
#include <stddef.h>

#include <curses.h>

void init(void) {
    initscr();

    char grid[LINES][COLS];

    // for (int i = 0; i < LINES; i++) {
    //     for (int j = 0; j < COLS; j++) {
    //         grid[i][j] = 'E';
    //     }
    // }

    grid[0][0] = '.'; grid[0][1] = '#'; grid[0][2] = '#';
    grid[1][0] = '#'; grid[1][1] = '#'; grid[1][2] = '.';
    grid[2][0] = '.'; grid[2][1] = '#'; grid[2][2] = '.';

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            mvaddch(i, j, grid[i][j]);
        }
    }

    // addstr("Welcome to EDDIEOS.");  
}
