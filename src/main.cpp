#include <ncurses.h>
#include <rapidjson/document.h>
#include <iostream>
#include <unistd.h>
#include <locale.h>
#include <signal.h>

#include "display.h"
#include "plugins.h"

// $ Salsa file.txt
// $ Salsa --config
// $ Salsa -c 

Context context;
bool ready = false;

void ctrl_c(int signal)
{
    if(ready)
    {
        send_key("CTRL_C");
        context.render();
    }
}

void ctrl_z(int signal)
{
    if(ready)
    {
        send_key("CTRL_Z");
        context.render();
    }
}

int main (int argc, char *argv[])
{
    signal(SIGINT, ctrl_c); // block ctrl + c force end
    signal(SIGTSTP, ctrl_z); // block ctrl + z force end

    bool on = true;
    int ch = 0;

    setlocale(LC_ALL, "en_US.UTF-8");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    refresh();
    
    context.setup(20,20);

    //load_plugins("");

    if (has_colors()) {
        ready = true;

        while (on)
        {
            ch = getch();

            if (ch == 0) // ctrl @
            {
                send_key("CTRL_@");
            }
            else if (ch == 1) // ctrl A
            {
                send_key("CTRL_A");
            }
            else if (ch == 2) // ctrl B
            {
                send_key("CTRL_B");
            }
            else if (ch == 4) // ctrl D
            {
                send_key("CTRL_D");
            }
            else if (ch == 5) // ctrl E
            {
                send_key("CTRL_E");
            }
            else if (ch == 6) // ctrl F
            {
                send_key("CTRL_F");
            }
            else if (ch == 7) // ctrl G
            {
                send_key("CTRL_G");
            }
            else if (ch == 8) // ctrl H
            {
                send_key("CTRL_H");
            }
            else if (ch == 9) // tab / ctrl I
            {
                send_key("TAB");
            }
            else if (ch == 10) // ctrl J & M
            {
                send_key("CTRL_JM");
            }
            else if (ch == 11) // ctrl K
            {
                send_key("CTRL_K");
            }
            else if (ch == 12) // ctrl L
            {
                send_key("CTRL_L");
            }
            else if (ch == 14) // ctrl N
            {
                send_key("CTRL_N");
            }
            else if (ch == 15) // ctrl O
            {
                send_key("CTRL_O");
            }
            else if (ch == 16) // ctrl P
            {
                send_key("CTRL_P");
            }
            else if (ch == 17) // ctrl Q
            {
                send_key("CTRL_Q");
            }
            else if (ch == 18) // ctrl R
            {
                send_key("CTRL_R");
            }
            else if (ch == 19) // ctrl S
            {
                send_key("CTRL_S");
            }
            else if (ch == 20) // ctrl T
            {
                send_key("CTRL_T");
            }
            else if (ch == 21) // ctrl U
            {
                send_key("CTRL_U");
            }
            else if (ch == 22) // ctrl V
            {
                send_key("CTRL_V");
            }
            else if (ch == 23) // ctrl W
            {
                send_key("CTRL_W");
            }
            else if (ch == 24) // ctrl X
            {
                send_key("CTRL_X");
            }
            else if (ch == 25) // ctrl Y
            {
                send_key("CTRL_Y");
            }
            if (ch == 27) // escape / ctrl [
            {
                send_key("ESCAPE");
                on = false;
            }
            else if (ch == 28) // ctrl "\"
            {
                send_key("CTRL_\\");
            }
            else if (ch == 29) // ctrl ]
            {
                send_key("CTRL_]");
            }
            else if (ch == 30) // ctrl ^
            {
                send_key("CTRL_^");
            }
            else if (ch == 31) // ctrl _
            {
                send_key("CTRL__");
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
            else if (ch == KEY_DC || ch == 127)
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
            else if (ch >= 32 && ch <= 126) // other
            {
                std::string _str = std::string(1, char(ch));
                context.setChar(0, 0, _str);
                send_key(_str);
            }
            else
            {
                printw("UNKNOWN KEY: %d", ch);
            }
            flushinp();
            context.render();
        }
        endwin();
    }
    else
    {
        endwin();
        std::cerr << "Your terminal does not support coloured text, In order for Salsa to work properly, you need a terminal that supports coloured text" << std::endl;
        return 1;
    }
	return 0;
}