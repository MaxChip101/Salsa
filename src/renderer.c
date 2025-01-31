#include <stdlib.h>
#include <stdio.h>
#include "renderer.h"

int setup(Display* display, int width, int height)
{
    if(width <= 0 || height <= 0) {return(1);}
    display->width = width;
    display->height = height;
    display->buffer = malloc(sizeof(Cell) * width * height);
    if(display->buffer == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for display");
        return(1);
    }
    return(0);
}

int set_pixel(Display* display, int x, int y, Cell cell)
{
    if(x < 0 || y < 0 || x >= display->width || y >= display->height) {return(1);}
    display->buffer[x + y * display->width] = cell;
    return(0);
}

int render(Display* display)
{
    printf("\033[H");
    for(int x = 0; x < display->width; x++)
    {
        for(int y = 0; y < display->height; y++)
        {
            printf("%s", display->buffer[x + y * display->width].value);
        }
        printf("%c", '\n');
    }
    fflush(stdout);
    return(0);
}

/*
int resize(Display display, int width, int height)
{
    realloc();
}
*/

int destroy(Display* display)
{
    free(display->buffer);
    return(0);
}

void create_buffer()
{
    printf("\033[?1049h"); // create and enter buffer
    printf("\033[H\033[J"); // clear buffer 

}

void clear_buffer()
{
    printf("\033[H\033[J"); // clear buffer
}

void original_buffer()
{
    printf("\033[H\033[J"); // clear buffer 
    printf("\033[?1049l"); // disable alternate buffer 
}
 