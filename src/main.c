#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../kernel/include/ps1.h"

#define DELAY 50000

void display_binary(WINDOW *win, const char *text, const char *status) {
    //char b_text[256] = {0};
    //char b_status[32] = {0};

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

void display_cogitator(WINDOW *win, const char *text) {
    wclear(win);
    wprintw(win, "%s", text);
    wrefresh(win);
    /**int offset = 0;
    int paused = 0;
    int text_len = strlen(text);

    int height, width;
    getmaxyx(stdscr, height, width);

    WINDOW *win = newwin(height - 2, width, 2, 0);

    mvprintw(0, 0, "Shortcuts: [Arrow Keys] Scroll \t [P]ause, Resume \t [Q]uit");
    refresh();

    while (1) {

        if (!paused) {
            wclear(win);
            for (int i = offset; i < text_len; i++) {
                wprintw(win, "%c", text[i]);
            }
            display_binary(win, text, "OK");
            wrefresh(win);
            offset++;
            if (offset >= text_len) offset = 0;
        }


        int ch = getch();
        switch (ch) {

        }

        usleep(DELAY);
    }
   **/ endwin();
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

void display_inst(WINDOW *win) {

    mvwprintw(win, 0, 0, "Shortcuts: [Arrow Keys] Scroll \t [P]ause, Resume \t [Q]uit");
}

void await_input(WINDOW *text_win, WINDOW *inst_win, const char *text) {
    int offset = 0;
    int paused = 0;
    int text_len = strlen(text);

    display_inst(inst_win);

    while (1) {
        if (!paused) {
            wclear(text_win);
            for (int i = offset; i < text_len; i++) {
                wprintw(text_win, "%c", text[i]);
            }
            wrefresh(text_win);
        }
        int ch = getch();

        switch (ch) {
            case KEY_UP:
                if (offset > 0) offset--;
                break;
            case KEY_DOWN:
                if (offset < text_len - 1) offset++;
                break;
            case ' ':
                paused = !paused;
                break;
            case 'r' : case'R':
                offset = 0;
                break;
            case 'q' : case'Q':
                endwin();
                return;
        }
    }
}

int main() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

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
    const char *online_text = "COGITATOR ONLINE: MACHINE SPIRIT ACTIVE...";

    size_t line_count = sizeof(desc) / sizeof(desc[0]);

    for (size_t i = 0; i < line_count; i++) {
        display_text(win, desc[i]);
        display_binary(win, desc[i], status[i]);
        usleep(DELAY);
    }


    display_cogitator(win, welcome_msg);
    refresh();
    usleep(DELAY * 10);
    display_transition(win, welcome_msg, online_text);
    refresh();

    getch();
    delwin(win);
    endwin();
    return 0;
}