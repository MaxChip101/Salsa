#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <wchar.h>

#define create_buffer() (printf("\033[?1049h"))
#define original_buffer() (printf("\033[?1049l"))
#define reset_cursor() ( printf("\033[H"))

#define disable_cursor() (printf("\033[?25l"))
#define endable_cursor() (printf("\033[?25h"))

typedef struct {
    wchar_t value;
    int x;
    int y;
} Cell;

typedef struct {
    Cell* cells;
    int size;
    int width;
    int height;
} Display;

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
    int z_layer;
} Widget;

Display setup(int width, int height);
int set_cell(Display* display, int x, int y, Cell cell);
int render(Display* display);
int destroy(Display* display);

#endif
