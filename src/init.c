#include <unistd.h>
#include <stddef.h>

#include <curses.h>

int get(char world[LINES][COLS], int i, int j) {
    if (i < 0)
        return 0;
    else if (i == LINES)
        return 0;
    else if (j < 0)
        return 0;
    else if (j == COLS)
        return 0;
    else
        return world[i][j];
}

int get_num_neighbors(char world[LINES][COLS], int i, int j) {
    int num_neighbors = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0)
                continue;

            num_neighbors += get(world, i+di, j+dj);
        }
    }

    return num_neighbors;
}

void init(void) {
    initscr();

    char world[LINES][COLS];
    char next[LINES][COLS];

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            world[i][j] = 0;
            next[i][j] = 0;
        }
    }

    // init
    world[0][0] = 0; world[0][1] = 1; world[0][2] = 1;
    world[1][0] = 1; world[1][1] = 1; world[1][2] = 0;
    world[2][0] = 0; world[2][1] = 1; world[2][2] = 0;

    // update
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            int neighbors = get_num_neighbors(world, i, j);

            if (world[i][j] == 1 && neighbors < 2)
                next[i][j] = 0; // underpopulation
            else if (world[i][j] == 1 && (neighbors == 2 || neighbors == 3))
                next[i][j] = 1; // survival
            else if (world[i][j] == 1 && neighbors > 3)
                next[i][j] = 0;  // overpopulation
            else if (world[i][j] == 0 && neighbors == 3)
                next[i][j] = 1; // reproduction
        }
    }

    // draw
    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            mvaddch(i, j, next[i][j] == 1 ? '#' : '.');
        }
    }

    // addstr("Welcome to EDDIEOS.");  
}
