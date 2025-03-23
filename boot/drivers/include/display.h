#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

// Public kernel API
void print_string(char* str);
void print_nl();
void clear_screen();
int scroll_in(int offset);