#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

#define create_buffer() (printf("\033[?1049h"))
#define original_buffer() (printf("\033[?1049l"))
#define reset_cursor() ( printf("\033[H"))

Display setup(int width, int height) {
    int size = width * height;
    Cell* cells = calloc(size, sizeof(Cell));
    if(cells == NULL) {
        Display err = {NULL, 0, 0, 0};
        return err;
    }

    for(int i = 0; i < size; i++) {
        cells[i].value = L'~';
    }

    Display display = {cells, size, width, height};
    return display;
}

int set_cell(Display* display, int x, int y, Cell cell) {
    if(x < 0 || x >= display->width || y < 0 || y >= display->height) {
        return 1;
    }
    display->cells[x + y * display->width] = cell;
    return 0;
}

int render(Display* display) {
    reset_cursor();
    for(int y = 0; y < display->height; y++) {
        for(int x = 0; x < display->width; x++) {
            if(display->cells[x + y * display->width].value == 0) {
                printf(" ");
                continue;
            }
            printf("%lc", display->cells[x + y * display->width].value);
        }
        if (y < display->height - 1) {
            printf("%c", '\n');
        }
    }
    fflush(stdout);

    return 0;
}

int destroy(Display* display) {
    free(display->cells);
    display->cells = NULL;
    return 0;
}