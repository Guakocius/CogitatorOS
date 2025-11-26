#include <cog/tty.h>
#include <cog/kernel.h>
#include <stdio.h>

void kernel_main(void) {
  terminal_initialize();
  terminal_writeln("Hello, World!");
  terminal_write("Status: ");
  print_ok();
  terminal_putchar('\n');
  terminal_write("Test fail: ");
  print_err();
  terminal_putchar('\n');

  for (;;) {
    __asm__ __volatile__("hlt");
  }
}
