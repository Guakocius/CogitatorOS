#include "../kernel/include/status.h"
#include "../kernel/include/status_check.h"
#include "../kernel/include/display.h"


Status statuses[] = {
        {"Initiating cogitator core protocols", check_hardware},
        {"Loading machine spirit modules", check_diagnostic},
        {"Establishing network connections", check_network},
        {"Initializing data storage", check_network},
        {"Configuring data sanctum", check_network},
        {"Performing system diagnostics", check_diagnostic},
        {"Verifying purity seals", check_hardware},
        {"Establishing noospheric uplink", check_network},
        {"Finalizing cogitation protocols", check_hardware},
        {"Activating machine spirit", check_hardware},
};

const int status_count = sizeof(statuses) / sizeof(Status);

void init_status() {
    for (int i = 0; i < status_count; i++) {
        statuses[i].check_fn = statuses[i].check_fn;
    }
}

void display_status(WINDOW *win, Status *status) {
    int width;
    int height;
    getmaxyx(win, height, width);

    mvwprintw(win, 0, 0, "%s", status->desc);

    char bin_code[9];
    snprintf(bin_code, sizeof(bin_code), "%08d", status->check_fn());
    mvwprintw(win, 0, width - 20, "Code: %s", bin_code);

    char bin_status[40] = {0};

    // Display OK or FAIL
    if (status->check_fn() == 0) {
        wattron(win, COLOR_PAIR(1));
        display_binary(win, bin_status, "OK");
        mvwprintw(win, 1, 0, "%s", bin_status);
        wattroff(win, COLOR_PAIR(1));
    } else {
        wattron(win, COLOR_PAIR(2));
        display_binary(win, bin_status, "FAIL");
        mvwprintw(win, 1, 0, "%s", bin_status);
        wattroff(win, COLOR_PAIR(2));
    }
    wrefresh(win);
}

