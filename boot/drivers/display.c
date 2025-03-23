#include "ports.h"
#include "display.h"
#include "util.h"

void set_cursor(int offset) {
    offset /= 2;
    port_byte_out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REG, (unsigned char)(offset >> 8));
    port_byte_out(VGA_CTRL_REG, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REG, (unsigned char)(offset & 0xff));
}

int get_cursor() {
    port_byte_out(VGA_CTRL_REG, VGA_OFFSET_HIGH);
    int offset = port_byte_in(VGA_DATA_REG) << 8;
    port_byte_out(VGA_CTRL_REG, VGA_OFFSET_LOW);
    offset += port_byte_in(VGA_DATA_REG);
    return offset * 2;
}

void set_char_at_video_memory(char c, int offset) {
    unsigned char* vidmem = (unsigned char*) VIDEO_ADDRESS;
    vidmem[offset] = c;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

int get_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

int get_row_from_offset(int offset) {
    return offset / (2 * MAX_COLS);
}

int move_offset_to_new_line(int offset) {
    return get_offset(0, get_row_from_offset(offset) + 1);
}

void print_string(char* str) {
    int offset = get_cursor();
    int i = 0;
    while (str[i] != 0) {
        if (offset >= MAX_ROWS * MAX_COLS * 2) {
            offset = scroll_in(offset);
        }
        if (str[i] == '\n') {
            offset = move_offset_to_new_line(offset);
        } else {
            set_char_at_video_memory(str[i], offset);
            offset += 2;
        }
        i++;
    }
    set_cursor(offset);
}

void print_nl() {
    int newOffset = move_offset_to_new_line(get_cursor());
    if (newOffset >= MAX_ROWS * MAX_COLS * 2) {
        newOffset = scroll_in(newOffset);
    }
    set_cursor(newOffset);
}

int scroll_in(int offset) {
    memory_copy(
        (char*) (get_offset(0, 1) + VIDEO_ADDRESS),
        (char*) (get_offset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2
    );

    for (int col = 0; col < MAX_COLS; col++) {
        set_char_at_video_memory(' ', get_offset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}

void clear_screen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
        set_char_at_video_memory(' ', i * 2);
    }
    set_cursor(get_offset(0, 0));
}