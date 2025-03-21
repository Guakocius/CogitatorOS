#include "../kernel/include/display.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define DELAY 50000

void to_binary(char *output, const char *input) {
    while (*input) {
        for (int i = 7; i >= 0; i--) {
            *output++ = (*input & (1 << i)) ? '1' : '0';
        }
        *output++ = ' ';
        input++;
    }
    *output = '\0';
}

void display_binary(WINDOW *win, const char *text, const char *status) {
    int win_width, y, x;
    getmaxyx(win, y, win_width);
    getyx(win, y, x);
    //wclear(win);

    char bin_text[512] = {0}; // Adjust size as needed
    char bin_stat[512] = {0}; // Adjust size as needed

    to_binary(bin_text, text);
    to_binary(bin_stat, status);

    mvwprintw(win, y, 1, "%s", bin_text);

    if (strcmp(status, "OK") == 0) {
        wattron(win, COLOR_PAIR(1));
        wrefresh(win);
    }
    else if (strcmp(status, "FAIL") == 0) {
        wattron(win, COLOR_PAIR(2));
        wrefresh(win);
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

    char *buffer = (char *)malloc(max_len + 1);
    if (buffer == NULL) {
        // Handle memory allocation failure
        return;
    }
    strcpy(buffer, curr_msg);

    for (int i = 0; i < max_len; i++) {
        if (i < len2) {
            buffer[i] = nxt_msg[i];
        }
        else {
            buffer[i] = ' ';
        }
        buffer[i + 1] = '\0';

        display_cogitator(win, buffer);
        usleep(DELAY);
    }

    free(buffer);
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