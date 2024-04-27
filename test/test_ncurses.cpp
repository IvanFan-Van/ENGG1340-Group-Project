#include <cstring>
#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>

int main() {
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);

  WINDOW *menu_win = newwin(max_y, max_x, 0, 0);
  WINDOW *game_win = newwin(max_y, max_x, 0, 0);
  WINDOW *items_win = newwin(max_y, max_x, 0, 0);

  PANEL *menu_panel = new_panel(menu_win);
  PANEL *game_panel = new_panel(game_win);
  PANEL *items_panel = new_panel(items_win);

  const char *menu_panel_title = "GAME MENU";
  const char *game_panel_title = "GAME WINDOW";
  const char *items_panel_title = "ITEMS";
  mvwprintw(menu_win, 0, 0, menu_panel_title);
  mvwprintw(game_win, 0, 0, game_panel_title);
  mvwprintw(items_win, 0, 0, items_panel_title);

  const char *menu_text = "F1 to switch to menu panel";
  const char *game_text = "F2 to switch to game panel";
  const char *items_text = "F3 to switch to items panel";
  mvwprintw(menu_win, max_y / 2, (max_x - strlen(menu_text)) / 2, "%s",
            menu_text);
  mvwprintw(game_win, max_y / 2, (max_x - strlen(game_text)) / 2, "%s",
            game_text);
  mvwprintw(items_win, max_y / 2, (max_x - strlen(items_text)) / 2, "%s",
            items_text);

  // set_panel_userptr(menu_panel, "GAME MENU");
  // set_panel_userptr(game_panel, "GAME WINDOW");
  // set_panel_userptr(items_panel, "ITEMS");

  update_panels();
  doupdate();

  int ch;
  while ((ch = getch()) != 'q') {
    switch (ch) {
    case '1':
      top_panel(menu_panel);
      break;
    case '2':
      top_panel(game_panel);
      break;
    case '3':
      top_panel(items_panel);
      break;
    }
    update_panels();
    doupdate();
  }

  endwin();
  return 0;
}