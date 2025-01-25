#include "../kernel/include/ps1.h"
#include "../kernel/include/display.h"
#include "../kernel/include/input.h"
#include "../kernel/include/status.h"
#include "../kernel/include/messages.h"
#include "../kernel/include/console.h"
#include "../kernel/include/disk.h"
#include "../kernel/include/state.h"

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

    const char *current_msg = "";
    const char *next_msg = welcome_msg;

    while(1) {
        display_transition(win, current_msg, next_msg);
        refresh();
        usleep(DELAY * 10);

        current_msg = next_msg;

        if (strcmp(current_msg, welcome_msg) == 0) {
            next_msg = online_msg;
        } else if (current_msg == online_msg) {
            next_msg = desc_init;
        } else if (strcmp(current_msg, desc_init) == 0) {
            for (int i = 0; i < status_count; i++) {
                wclear(win);
                display_status(win, &statuses[i]);
                usleep(DELAY);
            }
            next_msg = status_done;
        } else if (strcmp(current_msg, status_done) == 0) {
            wclear(win);
            display_inst(win);
            wrefresh(win);
            break;
        }
    }

    getch();
    delwin(win);
    endwin();
    return 0;
}