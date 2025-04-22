#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/ioctl.h>

#include "input.h"
#include "renderer.h"
#include "log.h"

void ctrl_c(int) {

}

void ctrl_z(int) {

}


void get_terminal_size(int *width, int *height) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

int main() {
    signal(SIGINT, ctrl_c); // block ctrl + c force end
    signal(SIGTSTP, ctrl_z); // block ctrl + z force end
    int width, height;
    get_terminal_size(&width, &height);
    disable_cursor();
    Display display = setup(width, height);
    enable_raw_mode();
    create_buffer();
    if(log_initiate() == 1) {
        original_buffer();
        disable_raw_mode();
        destroy(&display);
        endable_cursor();
        printf("salsa: failed to initialize logger\n");
        return 1;
    }

    int posx = 0;
    int posy = 0;

    while(1) {
        render(&display);
        char key = get_key();
        if(key == 27) { // escape
            break; // exit
        } if(key == '\n' && posy < height) {
            posx = 0;
            posy++;
        } else if(posx < width) {
            
            Color fg = {255, 255, 0};
            Color bg = {255, 0, 0};
            Cell cell = {(wchar_t)key, bg, fg, ATTRIBUTE_BOLD, posx, posy};
            set_cell(&display, posx, posy, cell);
            
            char* string;
            asprintf(&string, "x:%d, y:%d, w:%d, h:%d", posx, posy, width, height);
            log_write(string, "INFO", "main.c");
            free(string);
            string = NULL;
            
            posx++;
        }
    }
    original_buffer();
    disable_raw_mode();
    destroy(&display);
    endable_cursor();
    log_end();
    return 0;
}
