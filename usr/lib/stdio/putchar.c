#include <stdio.h>

#if defined(__is_libk)
#include <cog/tty.h>
#endif

int putchar(int ic) {
#if defined(__is_libk)
  char c = (char)ic;
  terminal_write(&c);
#else
  // TODO: Implement stdio and the write syscall
#endif
  return ic;
}
