#ifndef RENDERER_H
#define RENDERER_H

#include <stdio.h>
#include <wchar.h>
#include <stdint.h>

#define ATTRIBUTE_NONE      0x0
#define ATTRIBUTE_BOLD      0x01
#define ATTRIBUTE_ITALIC    0x02
#define ATTRIBUTE_UNDERLINE 0x04
#define ATTRIBUTE_BLINK     0x08
#define ATTRIBUTE_REVERSE   0x16
#define ATTRIBUTE_STRIKE    0x32

#define create_buffer() (printf("\033[?1049h"))
#define original_buffer() (printf("\033[?1049l"))
#define reset_cursor() (printf("\033[H"))

#define disable_cursor() (printf("\033[?25l"))
#define endable_cursor() (printf("\033[?25h"))

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

typedef struct {
    wchar_t value;
    Color bg;
    Color fg;
    uint8_t attributes;
} Cell;

typedef struct {
    Cell* cells;
    int size;
    int id;
    int x1;
    int y1;
    int x2;
    int y2;
    int z_layer;
} Widget;
// create focused widget
typedef struct {
    Widget* widgets;
    int size;
    int width;
    int height;
} Display;



Widget create_widget(int x1, int y1, int x2, int y2, int z_layer);
int set_cell(Widget* widget, int x, int y, Cell cell);
Cell get_cell(Widget widget, int x, int y);
int render_display(Display display);
int add_widget(Display* display, Widget widget);
int remove_widget(Display* display, Widget widget);
int destroy_widget(Widget* display);

#endif
