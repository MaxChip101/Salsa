#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "input.h"
#include "renderer.h"

void ctrl_c() {

}

void ctrl_z() {

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
    height-=1;
    Display display;
    setup(&display, width, height);
    enable_raw_mode();
    create_buffer();

    int on = 1;

    int posx = 0;
    int posy = 0;

    while(on) {
        char key = get_key();
        if(key == 27) { // escape
            on = 0; // exit
        } if(key == '\n' && posy < height - 1) {
            posx = 0;
            posy++;
        } else if(posx < width) {
            char* _str = {(char*) key};
            set_cell(&display, posx, posy, _str);
 
        }
        render(&display);
    }
    original_buffer();
    disable_raw_mode();
    destroy(&display);
    return 0;
}
