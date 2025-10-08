#include "util.h"

void memory_copy(char* source, char* dest, int nbytes) {
    for (int i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

char* int_to_string(int n, char* buff, int base) {
    static const unsigned char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char* p = buff;
    unsigned int num = (n < 0 && base == 10) ? -n : (unsigned int) n;

    // Build digits in reverse
    char* start = p;
    if (n < 0 && base == 10) {
        *p++ = '-';
        start = p;
    }

    // Extract digits (they come out in reverse order)
    char* digit_start = p;
    do {
        *p++ = (char) table[num % base];
        num /= base;
    } while (num > 0);
    *p = '\0';

    // Reverse the digit string
    char* end = p - 1;
    while (digit_start < end) {
        char temp = *digit_start;
        *digit_start = *end;
        *end = temp;
        digit_start++;
        end--;
    }

    return buff;
}