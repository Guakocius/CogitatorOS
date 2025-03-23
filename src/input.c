#include "input.h"
#include "display.h"

#include <ncurses.h>
#include <string.h>


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