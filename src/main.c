#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <wchar.h>

#include "input.h"
#include "renderer.h"
#include "log.h"
#include "configs.h"

void ctrl_c(int)
{
}

void ctrl_z(int)
{
}

void get_terminal_size(int *width, int *height)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *width = w.ws_col;
    *height = w.ws_row;
}

int main()
{
    signal(SIGINT, ctrl_c);  // block ctrl + c force end
    signal(SIGTSTP, ctrl_z); // block ctrl + z force end
    if (log_initiate() == 1)
    {
        printf("salsa: failed to initialize logger\n");
        return 1;
    }

    get_configurations();

    int width, height;
    get_terminal_size(&width, &height);
    Display display = create_display(width, height);
    disable_cursor();
    enable_raw_mode();
    create_buffer();

    int posx = 0;
    int posy = 0;

    Widget test = create_widget(0, 0, width, height, 0);
    add_widget(&display, test);
    while (1)
    {
        render_display(display);
        char key = get_key();
        if (key == 27)
        { // escape
            char next = next_key(1000);
            if (next == '[')
            {
                char next2 = next_key(1000);
                if (next2 == 'A' && posy > 0)
                {
                    posy++;
                }
                else if (next2 == 'B' && posy < height)
                {
                    posy--;
                }
                else if (next2 == 'C' && posx < width)
                {
                    posx++;
                }
                else if (next2 == 'D' && posx > 0)
                {
                    posx--;
                }
                next_key(0);
            }
            else
            {
                break; // exit
            }
        }
        if (key == '\n' && posy < height)
        {
            posx = 0;
            posy++;
        }
        else if (key == 127 && posx > 0)
        {
            posx--;
            Cell cell = {L'\0', {0, 0, 0}, {255, 255, 255}, ATTRIBUTE_NONE};
            set_cell(&test, posx, posy, cell);
        }
        else if (posx < width)
        {
            Cell cell = {(wchar_t)key, {0, 0, 0}, {255, 255, 255}, ATTRIBUTE_BOLD};
            set_cell(&test, posx, posy, cell);

            char *string;
            asprintf(&string, "x:%d, y:%d, w:%d, h:%d", posx, posy, width, height);
            LOG_INFO(string);
            free(string);
            string = NULL;

            posx++;
        }
        Cell cursor = {L'~', {255, 255, 255}, {20, 0, 0}, ATTRIBUTE_BOLD | ATTRIBUTE_BLINK};
        set_cell(&test, posx, posy, cursor);
    }
    original_buffer();
    disable_raw_mode();
    destroy_widget(&test);
    endable_cursor();
    log_end();
    return 0;
}
