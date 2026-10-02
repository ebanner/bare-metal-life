#include "curses.h"

int noecho() { return OK; }
int curs_set(int) { return OK; }
int getch(void) { return ERR; }
int nodelay(WINDOW*, int) { return OK; }
int leaveok(WINDOW*, int) { return OK; }
int scrollok(WINDOW*, int) { return OK; }
int refresh(void) { return OK; }
int mvcur(int, int, int, int) { return OK; }
int endwin(void) { return OK; }

int mvaddch(int y, int x, const char ch) {
  volatile unsigned short *vga = (volatile unsigned short *)0xB8000;

  int offset = 80*y + x;
  vga[offset] = 0x0F00 | ch; /* 0x0F00 is white on black */

  return OK;
}

void initscr() {
  for (int y = 0; y < LINES; y++)
      for (int x = 0; x < COLS; x++)
         mvaddch(y, x, ' ');
}

int CURSOR = 0;

int addch(const chtype ch) {
  volatile unsigned short *vga = (volatile unsigned short *)0xB8000;

  vga[CURSOR] = ch;

  CURSOR += 1;

  return OK;
}

int addstr(const char *str) {
  for ( ; *str != '\0'; str++) {
    addch(0x0F00 | *str);
  }
}