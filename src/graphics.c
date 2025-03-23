#include "graphics.h"

extern void set_video_mode();
extern void draw_px(int x, int y, unsigned char color);

void init_graphics() {
    set_video_mode();
}

void put_px(int x, int y, unsigned char color) {
    draw_px(x, y, color);
}