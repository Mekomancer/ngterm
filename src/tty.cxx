module;
#include <curses.h>
export module tty;

export void init_tty();
export void cleanup_tty();

void init_tty(){
  initscr();
  cbreak();
  noecho();
  curs_set(0);
}

void cleanup_tty(){
  endwin();
}

