#ifndef VIDEO_DRIVER_H
#define VIDEO_DRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);

void drawRectangle(uint64_t hexColor, uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void drawSquare(uint64_t hexColor, uint32_t x, uint32_t y, uint32_t width);



#endif