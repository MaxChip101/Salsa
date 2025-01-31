#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "input.h"
#include "renderer.h"

void ctrl_c()
{

}

void ctrl_z()
{

}

int main()
{
    signal(SIGINT, ctrl_c); // block ctrl + c force end
    signal(SIGTSTP, ctrl_z); // block ctrl + z force end

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return 1;
    }

    Display display;

    create_buffer();
    setup(&display, w.ws_col, w.ws_row);
    start_input();

    int on = 1;

    while(on)
    {
        char key = get_key();
        if(key == 27)
        {
            on = 0;
        }

        const char _str[1] = {key};
        Cell cell;
        strcpy(cell.value, _str);

        set_pixel(&display, 0, 0, cell);
        
        clear_buffer();
        render(&display);
        
        
    }
    destroy(&display);
    original_buffer();
    end_input();
}