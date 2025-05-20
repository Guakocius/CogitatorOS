#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>

void await_input(WINDOW *text_win, WINDOW *inst_win, const char *text);

#endif // INPUT_H