#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>
#include "status.h"

void to_binary(char *output, const char *input);
void display_binary(WINDOW *win, const char *text, const char *status);
void display_text(WINDOW *win, const char *text);
void display_cogitator(WINDOW *win, const char *text);
void display_transition(WINDOW *win, const char *curr_msg, const char *nxt_msg);
void display_inst(WINDOW *win);
void display_status(WINDOW *win, Status *status);

#endif // DISPLAY_H