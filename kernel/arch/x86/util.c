#include "util.h"

void memory_copy(char* source, char* dest, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

char* int_to_string(int n, char* buff, int base) {
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* p = buff;
    unsigned int num = (n < 0 && base == 10) ? -n : (unsigned int) n;
    while (num >= base) {
        *p++ = table[num % base];
        num /= base;
    } 
    *p++ = table[num];
    if (n < 0 && base == 10) *p++ = '-';
    *p = '\0';
    return buff;
}