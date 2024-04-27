#include <ncursesw/ncurses.h>

int main() {
  initscr();
  mvprintw(0, 0, "Hello, ncurses (wide character version)!");
  refresh();
  getch();
  endwin();
  return 0;
}