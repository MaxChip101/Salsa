#ifndef RENDERER_H
#define RENDERER_H

typedef struct {
    char* value;
    int size;
    int x;
    int y;
} Cell;

typedef struct {
    Cell* cells;
    int size;
} CellArray;

typedef struct {
    CellArray buffer;
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

int setup(Display* display, int width, int height);
int set_cell(Display* display, int x, int y, char* cell);
int render(Display* display);
int destroy(Display* display);
void create_buffer();
void original_buffer();

#endif