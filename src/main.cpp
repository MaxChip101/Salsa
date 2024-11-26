#include <ncurses.h>
#include <rapidjson/document.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>

#include "display.h"
#include "plugins.h"

// $ Salsa file.txt
// $ Salsa --config
// $ Salsa -c 

void ctrl_c(int signal)
{
    send_key("CTRL_C");
}

void ctrl_z(int signal){
    send_key("CTRL_Z");
}

int main (int argc, char *argv[])
{
    signal(SIGINT, ctrl_c); // block ctrl + c force end
    signal(SIGTSTP, ctrl_z); // block ctrl + z force end

    int ch;
    bool on = true;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();

    if (has_colors()) {
        while (on)
        {
            // input
            ch = getch();

            if (ch >= 1 && ch <= 26) // ctrl a-z
            {
                send_key("CTRL_" + char(ch+64));
            }
            else if (ch == 27) // escape
            {
                send_key("ESCAPE");
                on = false; // temporary but a failsave
            }
            else if (ch == KEY_UP)
            {
                send_key("UP");
            }
            else if (ch == KEY_DOWN)
            {
                send_key("DOWN");
            }
            else if (ch == KEY_LEFT)
            {
                send_key("LEFT");
            }
            else if (ch == KEY_RIGHT)
            {
                send_key("RIGHT");
            }
            else if (ch == KEY_BACKSPACE)
            {
                send_key("BACKSPACE");
            }
            else if (ch == KEY_HOME)
            {
                send_key("HOME");
            }
            else if (ch == KEY_END)
            {
                send_key("END");
            }
            else if (ch == KEY_PPAGE)
            {
                send_key("PAGE_UP");
            }
            else if (ch == KEY_NPAGE)
            {
                send_key("PAGE_DOWN");
            }
            else if (ch >= 265 && ch <= 274) // f1-f10
            {
                send_key("F" + char(ch - 264));
            }
            else if (ch == KEY_DC)
            {
                send_key("DELETE");
            }
            else if (ch == KEY_IC)
            {
                send_key("INSERT");
            }
            else if (ch == KEY_SF)
            {
                send_key("SCROLL_DOWN");
            }
            else if (ch == KEY_SR)
            {
                send_key("SCROLL_UP");
            }
            else if (ch == KEY_A1)
            {
                send_key("HOME_1");
            }
            else if (ch == KEY_A3)
            {
                send_key("HOME_2");
            }
            else if (ch == KEY_C1)
            {
                send_key("END_1");
            }
            else if (ch == KEY_C3)
            {
                send_key("END_2");
            }
            else // other
            { 
                send_key(ch + "");
            }
        }
    endwin();
    } else {
        endwin();
        std::cerr << "Your terminal does not support coloured text, In order for Salsa to work properly, you need a terminal that supports coloured text" << std::endl;
        return 1;
    }
	return 0;
}