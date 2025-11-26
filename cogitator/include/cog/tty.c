#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <cog/kernel.h>
#include "vga.h"
#include <cog/tty.h>

static inline uint8_t vga_color(enum vga_color fg, enum vga_color bg) {
  return (uint8_t)(fg | (bg << 4));
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
  return (uint16_t)c | ((uint16_t)color << 8);
}

static size_t terminal_row = 0, terminal_col = 0;
static uint8_t terminal_color;

void terminal_setcolor(uint8_t color) {
  terminal_color = color;
}

static void terminal_clear(void) {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t idx = y * VGA_WIDTH + x;
      VGA_BUFFER[idx] = vga_entry(' ', terminal_color);
    }
  }
  terminal_row = 0, terminal_col = 0;
}

void terminal_initialize(void) {
  terminal_setcolor(vga_color(COLOR_LIGHT_GREY, COLOR_BLACK));
  terminal_clear();
}

static void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
  const size_t idx = y * VGA_WIDTH + x;
  VGA_BUFFER[idx] = vga_entry(c, color);
}

static void terminal_scroll(void) {
  for (size_t y = 1; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      VGA_BUFFER[(y - 1) * VGA_WIDTH + x] = VGA_BUFFER[y * VGA_WIDTH + x];
    }
  }

  for (size_t x = 0; x < VGA_WIDTH; x++) {
    VGA_BUFFER[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
  }
  if (terminal_row > 0) terminal_row--;
}
static void terminal_delete_last_line() {
  for (size_t x = 0; x < VGA_WIDTH; x++) {
    const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
    VGA_BUFFER[index] = vga_entry(' ', terminal_color);
  }
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_col = 0;
    terminal_row++;
    if (terminal_row >= VGA_HEIGHT) {
      terminal_scroll();
    }
    return;
  }

  terminal_putentryat((unsigned char)c, terminal_color, terminal_col, terminal_row);
  terminal_col++;
  if (terminal_col >= VGA_HEIGHT) {
    terminal_col = 0;
    terminal_row++;
    if (terminal_row >= VGA_HEIGHT) {
      terminal_scroll();
    }
  }
}

void terminal_write(const char* str) {
  while (*str) {
    terminal_putchar(*str++);
  }
}

void terminal_writeln(const char* str) {
  terminal_write(str);
  terminal_putchar('\n');
}

void print_ok(void) {
  uint8_t old = terminal_color;
  terminal_setcolor(vga_color(COLOR_LIGHT_GREEN, COLOR_BLACK));
  terminal_write("[ok]");
  terminal_setcolor(old);
}

void print_err(void) {
  uint8_t old = terminal_color;
  terminal_setcolor(vga_color(COLOR_LIGHT_RED, COLOR_BLACK));
  terminal_write("[err]");
  terminal_setcolor(old);
}


