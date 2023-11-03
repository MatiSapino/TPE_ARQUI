#ifndef _VIDEO_DRIVER_H
#define _VIDEO_DRIVER_H

#include <stdint.h>

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WHITE 0xFFFFFF
#define BLACK 0x000000

#define COLORS (int[]) {GREEN, RED, WHITE, BLUE, BLACK}


#define isMinusc(x) ((x)<='a'?(((x)>='z')?1:0):0)
#define DEFAULT_FONT_SIZE 1

void changeSize(uint32_t new_size);
void newline();
void drawWordColor(uint64_t hexColor, char* word);
void drawWord(char* word);
void invalidFd(); //indica que el filedescriptor es invalido
void drawRegisters(int value);
void clear();
void drawCursor();
void deleteCursor();


#endif /* _VIDEO_DRIVER_H */