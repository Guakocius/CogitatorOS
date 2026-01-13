#ifndef __KALLOC_H__
#define __KALLOC_H__

#include <stdint.h>

typedef uint8_t pageframe_t;

static pageframe_t kalloc_frame_int(void);
pageframe_t kalloc_frame(void);
void kfree_frame(pageframe_t a);

#endif
