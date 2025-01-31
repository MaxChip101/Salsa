#ifndef RENDERER_H
#define RENDERER_H

typedef struct
{
    char value[5];
    char encoding[50];
} Cell;

typedef struct
{
    Cell* buffer;
    int width;
    int height;
} Display;

typedef struct
{
    int x1;
    int y1;
    int x2;
    int y2;
    int z_layer;
} Widget;

int setup(Display* display, int width, int height);
int set_pixel(Display* display, int x, int y, Cell cell);
int render(Display* display);
int destroy(Display* display);
void create_buffer();
void clear_buffer();
void original_buffer();

#endif