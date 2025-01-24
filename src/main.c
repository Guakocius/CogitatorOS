#include "../kernel/include/ps1.h"
#include "../kernel/include/display.h"
#include "../kernel/include/input.h"
#include "../kernel/include/status.h"
#include "../kernel/include/messages.h"
#include "../kernel/include/console.h"
#include "../kernel/include/disk.h"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELAY 50000

void setup_colors() {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

int main() {

    initscr();
    noecho();

    WINDOW *win = newwin(15, 60, 5, 10);
    setup_colors();
    display_cogitator(win, welcome_msg);
    refresh();
    usleep(DELAY * 10);
    display_transition(win, welcome_msg, online_msg);
    refresh();

    for (int i = 0; i < status_count; i++) {
        wclear(win);
        display_status(win, &statuses[i]);
        wrefresh(win);
        usleep(DELAY);
    }

    wclear(win);
    display_inst(win);
    wrefresh(win);

    getch();
    delwin(win);
    endwin();
    return 0;
}