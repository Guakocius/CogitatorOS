#include "../../drivers/include/display.h"
#include "./include/util.h"

int main(void) {
    clear_screen();
    print_string("CogitatorOS Kernel v0.1\n");
    print_string("========================\n");
    print_nl();
    print_string("Boot successful! Running in 32-bit protected mode.\n");
    print_nl();

    // Manual test without int_to_string
    print_string("Test 1: Manual strings work\n");

    // Test buffer manually
    char line[32];
    line[0] = '4';
    line[1] = '2';
    line[2] = '\0';
    print_string("Test 2: Manual buffer = ");
    print_string(line);
    print_nl();

    // Now test int_to_string
    print_string("Test 3: int_to_string(5) = ");
    int_to_string(5, line, 10);
    print_string(line);
    print_nl();

    print_nl();
    print_string("Counting test:\n");
    for (int i = 1; i <= 15; i++) {
        int_to_string(i, line, 10);
        print_string(line);
        print_string(" ");
        if (i % 10 == 0) print_nl();
    }
    print_nl();
    print_nl();
    print_string("Kernel finished. System halted.");

    // Infinite loop - never return from main
    while(1) {
        __asm__ volatile ("hlt");
    }
}