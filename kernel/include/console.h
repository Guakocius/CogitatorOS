#ifndef CONSOLE_H
#define CONSOLE_H
#include <ncurses.h>

void console_init();
void console_print(const char *str);
void console_clear();
void console_set_color(int color);

#endif // CONSOLE_H