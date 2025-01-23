#include "../kernel/include/ps1.h"
#include "display.c"
#include "input.c"

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    WINDOW *win = newwin(15, 60, 5, 10);

    // display messages
    const char *desc[] = {
        "Initiating cogitator core protocols",
        "Loading machine spirit modules",
        "Configuring data sanctum",
        "Verifying purity seals",
        "Establishing noospheric uplink",
        "Finalizing cogitation protocols"
    };
    const char *status[] = {
        "OK", "OK", "OK", "FAIL", "OK", "OK"
    };
    const char *welcome_msg = "COGITATOR AWAKES: PLEASE WAIT...";
    const char *online_msg = "COGITATOR ONLINE: MACHINE SPIRIT ACTIVE...";

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