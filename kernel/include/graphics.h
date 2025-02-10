#ifndef GRAPHICS_H
#define GRAPHICS_H

void init_graphics();
void put_px(int x, int y, unsigned char color);
extern void set_video_mode();
extern void draw_px(int x, int y, unsigned char color);

#endif // GRAPHICS_H