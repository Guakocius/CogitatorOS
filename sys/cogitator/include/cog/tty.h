#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stdint.h>

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* str);
void terminal_writeln(const char* str);
static inline uint32_t read_cr0(void);
void check_paging(void);

#endif
