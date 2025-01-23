#include "../kernel/include/status.h"
#include "../kernel/include/display.h"


Status statuses[] = {
        {"Initiating cogitator core protocols", 0},
        {"Loading machine spirit modules", 0},
        {"Configuring data sanctum", 0},
        {"Verifying purity seals", 0},
        {"Establishing noospheric uplink", 0},
        {"Finalizing cogitation protocols", 0}
};

const int status_count = sizeof(statuses) / sizeof(Status);

void display_status(WINDOW *win, Status *status) {
    int width;
    int height;
    getmaxyx(win, height, width);

    mvwprintw(win, 0, 0, "%s", status->desc);

    char bin_code[9];
    snprintf(bin_code, sizeof(bin_code), "%08d", status->code);
    mvwprintw(win, 0, width - 20, "Code: %s", bin_code);

    // Display OK or FAIL
    if (status->code == 0) {
        wattron(win, COLOR_PAIR(1));
        mvwprintw(win, 0, width - 10, "OK");
        wattroff(win, COLOR_PAIR(1));
    } else {
        wattron(win, COLOR_PAIR(2));
        mvwprintw(win, 0, width - 10, "FAIL");
        wattroff(win, COLOR_PAIR(2));
    }
    wrefresh(win);
}

