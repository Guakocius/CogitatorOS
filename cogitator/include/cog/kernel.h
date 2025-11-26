#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdint.h>
#include <stddef.h>

static const size_t VGA_WIDTH = 80, VGA_HEIGHT = 25;

static uint16_t* const VGA_BUFFER = (uint16_t*)0xB8000;

void print_ok(void);
void print_err(void);


#endif // !_KERNEL_H
