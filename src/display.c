#include "../kernel/include/display.h"
#include <string.h>
#include <unistd.h>

#define DELAY 50000

void display_binary(WINDOW *win, const char *text, const char *status) {

    int win_width, y, x;
    getmaxyx(win, y, win_width);
    getyx(win, y, x);
    wclear(win);

    char bin_stat[64] = {0};

    for (size_t i = 0; i < strlen(status); i++) {
        char temp[9];

        for (int j = 7; j >= 0; j--) {
            temp[7 - j] = (status[i] & (1 << j)) ? '1' : '0';
        }
        temp[8] = '\0';
        strcat(bin_stat, temp);
        strcat(bin_stat, " ");
    }

    mvwprintw(win, y, 1, "%s", text);
    //wrefresh(win);

    if (strcmp(status, "OK") == 0) {
        wattron(win, COLOR_PAIR(1));
        wrefresh(win);
    } else if (strcmp(status, "FAIL") == 0) {
        wattron(win, COLOR_PAIR(2));
        //wrefresh(win);
    }

    mvwprintw(win, y, win_width - (int)strlen(bin_stat) - 2, "%s", bin_stat);

    wattroff(win, COLOR_PAIR(1));
    wattroff(win, COLOR_PAIR(2));

    wrefresh(win);
    usleep(DELAY);
}

void display_text(WINDOW *win, const char *text) {
    wclear(win);
    wprintw(win, "%s", text);
    wrefresh(win);
}

void display_transition(WINDOW *win, const char *curr_msg, const char *nxt_msg) {
    int len1 = strlen(curr_msg);
    int len2 = strlen(nxt_msg);
    int max_len = len1 > len2 ? len1 : len2;

    char buffer[max_len + 1];
    strcpy(buffer, curr_msg);

    for (int i = 0; i < max_len; i++) {
        if (i < len2) {
            buffer[i] = nxt_msg[i];
        } else {
            buffer[i] = ' ';
        }
        buffer[i + 1] = '\0';

        display_cogitator(win, buffer);
        usleep(DELAY);
    }
}

void display_cogitator(WINDOW *win, const char *text) {
    int win_width, y, x;
    getmaxyx(win, y, win_width);
    getyx(win, y, x);
    wclear(win);

    mvwprintw(win, y, (win_width - strlen(text)) / 2, "%s", text);
    wrefresh(win);
}

void display_inst(WINDOW *win) {

    mvwprintw(win, 0, 0, "Shortcuts: [Arrow Keys] Scroll \t [P]ause, Resume \t [Q]uit");
}