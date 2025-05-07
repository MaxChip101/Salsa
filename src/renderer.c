#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "renderer.h"

#define create_buffer() (printf("\033[?1049h"))
#define original_buffer() (printf("\033[?1049l"))

int last_widget_id = 1;

Widget create_widget(int x1, int y1, int x2, int y2, int z_layer) {
    int size = x2 * y2 ;
    Cell* cells = calloc(size, sizeof(Cell));
    if(cells == NULL) {
        Widget err = {NULL, 0, 0, 0, 0, 0, 0, 0};
        return err;
    }

    Widget widget = {cells, size, last_widget_id, x1, y1, x2, y2, z_layer};
    last_widget_id++;
    return widget;
}

int set_cell(Widget* widget, int x, int y, Cell cell) {
    if(x < 0 || x >= widget->x2 - widget->x1 || y < 0 || y >= widget->y2 - widget->y1) {
        return 1;
    }
    widget->cells[x + y * (widget.x2 - widget->x1)] = cell;
    return 0;
}

Cell get_cell(Widget widget, int x, int y) {
    if(x < 0 || x >= widget->x2 - widget->x1 || y < 0 || y >= widget->y2 - widget->y1) {
        Cell err = {L'\0', {0,0,0}, {0,0,0}, 0};
        return err;
    }
    return display->cells[x + y * (widget->x2 - widget->x1)];
}


// TODO: optimize later to use write()
int render_display(Display display) {
    reset_cursor();
    for(int y = 0; y < display->height; y++) {
        for(int x = 0; x < display->width; x++) {
            if(display->cells[x + y * display->width].value == 0) {
                printf(" ");
                continue;
            }

            Cell cell = display->cells[x + y * display->width];
            
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

// inserts widget depending on z_layer, 0 is far left and it goes to the right for every number
// create new widget pointer that inserts the widget in the proper position
// returns 0 for success, returns 1 for any memory errors
int add_widget(Display* display, Widget widget) {
    
}

// finds the widget and creates a new pointer that does not include the widget
// returns 0 for success, returns 1 for any memory errors, returns 2 if it does not exist
int remove_widget(Display* display, Widget widget) {

}

int destroy_widget(Widget* widget) {
    free(widget->cells);
    widget->cells = NULL;
    last_widget_id--;
    return 0;
}