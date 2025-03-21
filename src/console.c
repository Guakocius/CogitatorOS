#include "../kernel/include/console.h"
#include <stdio.h>

void console_print(const char *str) {
    printf("%s", str);
}

void console_init() {

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    attron(A_BOLD);
}

void console_clear() {
    printf("\033[H\033[J"); // Clear screen
}

void console_set_color(int color) {
    printf("\033[%dm", color); // Set color
}