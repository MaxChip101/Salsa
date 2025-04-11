#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

int setup(Display* display, int width, int height) {
    
}

int set_cell(Display* display, int x, int y, Cell cell) {

}

int render(Display* display) {
    
}

int destroy(Display* display) {

}

void create_buffer() {
    printf("\033[?1049h"); // create and enter buffer
    system("clear");
}

void original_buffer() {
    printf("\033[?1049l"); // disable alternate buffer 
}
 
