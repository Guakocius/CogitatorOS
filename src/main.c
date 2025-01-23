#include "../kernel/include/ps1.h"
#include "display.c"
#include "input.c"
#include "status.c"
#include "messages.c"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    WINDOW *win = newwin(15, 60, 5, 10);


    size_t line_count = sizeof(desc) / sizeof(desc[0]);

    for (size_t i = 0; i < line_count; i++) {
        display_text(win, desc[i]);
        display_binary(win, desc[i], status[i]);
        usleep(DELAY);
    }


    display_cogitator(win, welcome_msg);
    refresh();
    usleep(DELAY * 10);
    display_transition(win, welcome_msg, online_msg);
    refresh();

    getch();
    delwin(win);
    endwin();
    return 0;
}