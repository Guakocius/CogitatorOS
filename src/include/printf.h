#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>
#include <stddef.h>

#define printf _printf
int _printf(const char *format, ...);

#endif // !_PRINTF_H