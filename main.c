#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DELAY 100000

void display_binary(WINDOW *win, const char *text, int offset) {
    //char b_text[256] = {0};
    //char b_status[32] = {0};

    int len = strlen(text);
    wclear(win);

    for (int i = offset; i < len; i++) {

        for (int j = 7; j >= 0; j--) {
            wprintw(win, "%c", (text[i] & (1 << j)) ? '1' : '0');
        }
        wprintw(win, " ");
    }

    wrefresh(win);
}

void display_text(WINDOW *win, const char *text) {
    wclear(win);
    wprintw(win, "%s", text);
    wrefresh(win);
}

void display_cogitator (const char *text, int ) {
    int offset = 0;
    int paused = 0;
    int text_len = strlen(text);

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

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
            display_binary(win, text, offset);
            wrefresh(win);
            offset++;
            if (offset >= text_len) offset = 0;
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
            case 'r':case'R':
                offset = 0;
                break;
            case 'q':case'Q':
                endwin();
                return;
        }

        usleep(DELAY);
    }
    endwin();
}

void display_transition(const char *curr_msg, const char *nxt_msg) {
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
        display_cogitator(buffer);
        usleep(DELAY);
    }
}

int main() {
    const char *welcome_msg = "COGITATOR AWAKES: PLEASE WAIT...";
    const char *online_text = "COGITATOR ONLINE: MACHINE SPIRIT ACTIVE...";
    display_cogitator(welcome_msg);
    refresh();
    usleep(DELAY * 10);
    display_transition(welcome_msg, online_text);
    refresh();
    return 0;
}