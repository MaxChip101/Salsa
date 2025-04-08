#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"



void create_buffer() {
    printf("\033[?1049h"); // create and enter buffer
    system("clear");
}

void original_buffer() {
    printf("\033[?1049l"); // disable alternate buffer 
}
 