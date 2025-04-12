#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

Display setup(int width, int height) {
    int size = width * height;
    Cell* cells = calloc(size, sizeof(Cell));
    if(cells == NULL) {
        Display err = {NULL, 0, 0};
        return err;
    }
    CellArray array = {cells, size};
    Display display = {array, width, height};
    return display;
}

int set_cell(Display* display, int x, int y, Cell cell) {
    display->buffer.cells[x + y * display->width] = cell;
    return 0;
}

int render(Display* display) {
    printf("\033[0;0H");
    printf("\033[H");
    for(int i = 0; i < display->buffer.size; i++) {
        if(i % display->width == 0) {
            printf("%c", '\n');
            continue;
        }
        if(display->buffer.cells[i].value.value != NULL &&
            strcmp(display->buffer.cells[i].value.value, "\0") != 0) {
            printf("%s", display->buffer.cells[i].value.value);
        }
    }
    return 0;
}

int destroy(Display* display) {
    for(int i = 0; i < display->buffer.size; i++) {
        if(display->buffer.cells[i].value.value != NULL) {
            free(display->buffer.cells[i].value.value);
            display->buffer.cells[i].value.value = NULL;
        }
    }
    free(display->buffer.cells);
    display->buffer.cells = NULL;
    return 0;
}

void create_buffer() {
    printf("\033[?1049h"); // create and enter buffer
    system("clear");
}

void original_buffer() {
    printf("\033[?1049l"); // disable alternate buffer 
}
 
