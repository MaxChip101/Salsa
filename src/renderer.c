#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

#define create_buffer() (printf("\033[?1049h"))
#define original_buffer() (printf("\033[?1049l"))

Display setup(int width, int height) {
    int size = width * height;
    Cell* cells = calloc(size, sizeof(Cell));
    if(cells == NULL) {
        Display err = {NULL, 0, 0, 0};
        return err;
    }

    for(int i = 0; i < size; i++) {
        Cell cell = {L' ', {(int)(((float)(i % width)/(float)size) * 255), (int)(((float)i/(float)size) * 255), (int)(((float)i/(float)size) * 255)}, {0, 0, 0}, ATTRIBUTE_BOLD, 0, 0};
        cells[i] = cell;
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
            Cell cell = display->cells[x + y * display->width];
            // 1(bold) 3(italic) 4(underline) 5(blink) 7(reverse) 9(strike)
            // \033[attributes;38;2;r;g;b;48;2;r;g;bm
            printf("\033[%s%s%s%s%s%s38;2;%d;%d;%d;48;2;%d;%d;%dm%lc\033[0m",
                ((cell.attributes & ATTRIBUTE_BOLD) == ATTRIBUTE_BOLD) ? "1;" : "",
                ((cell.attributes & ATTRIBUTE_ITALIC) == ATTRIBUTE_ITALIC) ? "3;" : "",
                ((cell.attributes & ATTRIBUTE_UNDERLINE) == ATTRIBUTE_UNDERLINE) ? "4;" : "",
                ((cell.attributes & ATTRIBUTE_BLINK) == ATTRIBUTE_BLINK) ? "5;" : "",
                ((cell.attributes & ATTRIBUTE_REVERSE) == ATTRIBUTE_REVERSE) ? "7;" : "",
                ((cell.attributes & ATTRIBUTE_STRIKE) == ATTRIBUTE_STRIKE) ? "9;" : "",
                cell.fg.r,
                cell.fg.g,
                cell.fg.b,
                cell.bg.r,
                cell.bg.g,
                cell.bg.b,
                cell.value
            );
        }
        if (y < display->height - 1) {
            printf("\n");
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