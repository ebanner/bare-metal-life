#include <unistd.h>
#include <stddef.h>
#include <debug.h>

#include <curses.h>

int idx(int i) {
    // return (i < 0) ? LINES : (i == LINES) ? 0 : i;

    if (i < 0)
        return LINES-1;
    else if (i == LINES)
        return 0;
    else
        return i;
}

int jdx(int j) {
    // return (j < 0) ? COLS : (j == COLS) ? 0 : j;

    if (j < 0)
        return COLS-1;
    else if (j == COLS)
        return 0;
    else
        return j;
}

int get_num_neighbors(char world[LINES][COLS], int i, int j) {
    int num_neighbors = 0;
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            if (di == 0 && dj == 0)
                continue;

            num_neighbors += world[idx(i+di)][jdx(j+dj)];
        }
    }

    return num_neighbors;
}

void step(char world[LINES][COLS]) {
    char next[LINES][COLS];

    for (int i = 0; i < LINES; i++) {
        for (int j = 0; j < COLS; j++) {
            next[i][j] = 0;
        }
    }

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

    // copy back
    for (int i = 0; i < LINES; i++)
        for (int j = 0; j < COLS; j++)
            world[i][j] = next[i][j];
}

#define R_PENTOMINO 0
#define GLIDER 1

static const char R_PENTOMINO_NAME[] = "R-Pentomino";
static const char GLIDER_NAME[] = "Glider";

static int START_CONFIGURATION = R_PENTOMINO;

void _init(char world[LINES][COLS]) {
    for (int i = 0; i < LINES; i++)
        for (int j = 0; j < COLS; j++)
            world[i][j] = 0;

    if (START_CONFIGURATION == R_PENTOMINO) {
        world[12][40] = 0; world[12][41] = 1; world[12][42] = 0;
        world[13][40] = 0; world[13][41] = 0; world[13][42] = 1;
        world[14][40] = 1; world[14][41] = 1; world[14][42] = 1;

        START_CONFIGURATION = GLIDER;
    } else {
        world[12][40] = 0; world[12][41] = 1; world[12][42] = 1;
        world[13][40] = 1; world[13][41] = 1; world[13][42] = 0;
        world[14][40] = 0; world[14][41] = 1; world[14][42] = 0;

        START_CONFIGURATION = R_PENTOMINO;
    }
}

static inline unsigned char inb(unsigned short port) {
    unsigned char v;
    __asm__ volatile ("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

unsigned int kbd_poll() {
    unsigned char status = inb(0x64);
    if (status & 0x01 == 0)
        return 0;

    unsigned char key = inb(0x60);
    return key;
}

void init(void) {
    initscr();

    char welcome[] = "WELCOME TO EDDIEOS.";
    move(LINES/3, COLS/2-(sizeof(welcome)/2));
    attron(COLOR_YELLOW);
    addstr(welcome);
    attroff(0);

    usleep(5000000);

    char world[LINES][COLS];
    _init(world);

    // // Glider
    // world[12][40] = 0; world[12][41] = 1; world[12][42] = 0;
    // world[13][40] = 0; world[13][41] = 0; world[13][42] = 1;
    // world[14][40] = 1; world[14][41] = 1; world[14][42] = 1;

    for (;;) {
        // draw
        for (int i = 0; i < LINES; i++)
            for (int j = 0; j < COLS; j++)
                mvaddch(i, j, world[i][j] == 1 ? '#' : ' ');

        step(world);

        char title[] = "Conway's Game of Life";
        move(LINES-1, COLS-sizeof(title));
        attron(COLOR_GREEN);
        addstr(title);
        attroff(0);

        const char *start_configuration = (START_CONFIGURATION == R_PENTOMINO) ? R_PENTOMINO_NAME : GLIDER_NAME;
        move(LINES-1, 1);
        addstr(start_configuration);
        attroff(0);

        usleep(10000);

        unsigned int result = kbd_poll();
        if (result == 0)
            continue;

        if (result != 0x39)
            continue;

        _init(world);

        // dbg_puts("Space!\n");
    }
}
