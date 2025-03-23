#include "ps1.h"
#include "display.h"
#include "input.h"
#include "status.h"
#include "messages.h"
#include "console.h"
#include "disk.h"
#include "state.h"

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

    State current_state = WELCOME;
    const char *current_msg = "";
    const char *next_msg = welcome_msg;

    while(1) {
        display_transition(win, current_msg, next_msg);
        refresh();
        usleep(DELAY * 10);

        current_msg = next_msg;

        switch (current_state) {
            case WELCOME:
                next_msg = online_msg;
                current_state = ONLINE;
                break;
            case ONLINE:
                next_msg = desc_init;
                current_state = DESC_INIT;
                break;
            case DESC_INIT:
                for (int i = 0; i <  status_count; i++) {
                    wclear(win);
                    display_status(win, &statuses[i]);
                    usleep(DELAY);
                }
                next_msg = status_done;
                current_state = STATUS_DONE;
                break;
            case STATUS_DONE:
                wclear(win);
                display_inst(win);
                wrefresh(win);
                getch();
                delwin(win);
                endwin();
                return 0;
        }
    }
}