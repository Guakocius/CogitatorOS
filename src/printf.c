#include "include/os_stdio.h"

int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buf[256];
    int i = 0, j = 0;
    while (format[i] && j < sizeof(buf) - 1) {
        if (format[i] == '%' &&format[i + 1]) {
            i++;
            if (format[i] == 's') {
                char *s = va_arg(args, char*);
                while (*s && j < sizeof(buf) - 1) buf[j++] = *s++;
            } else if (format[i] == 'd') {
                int n = va_arg(args, int);
                char numbuf[32];
                int_to_string(n, numbuf, 10);
                char *p = numbuf;
                while (*p && j < sizeof(buf) - 1) buf[j++] = *p++;
            } else {
                buf[j++] = format[i];
            }
        } else {
            buf[j++] = format[i];
        }
        i++;
    }
    buf[j] = '\0';
    print_string(buf);
    va_end(args);
    return j;
}