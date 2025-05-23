#ifndef SHELL_H
#define SHELL_H

#include <ncurses.h>

#include "../../../../../src/include/os_stdio.h"

void display_binary(WINDOW *win, const char *text, const char *status);
void display_text(WINDOW *win, const char *text);
void display_cogitator(WINDOW *win, const char *text);
void display_transition(WINDOW *win, const char *curr_msg, const char *nxt_msg);
void display_inst(WINDOW *win);
void display_status(WINDOW *win, Status *status);

#endif // !SHELL_H