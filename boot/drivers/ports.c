#include "ports.h"

unsigned char port_byte_in(unsigned short port) {
    unsigned char result;
    // AT&T syntax: in source, dest (opposite of Intel syntax)
    __asm__ volatile ("inb %1, %0" : "=a" (result) : "dN" (port));
    return result;
}

void port_byte_out(unsigned short port, unsigned char data) {
    // AT&T syntax: out source, dest (opposite of Intel syntax)
    __asm__ volatile ("outb %0, %1" : : "a" (data), "dN" (port));
}