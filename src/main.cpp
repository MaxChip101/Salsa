#include <ncurses.h>
#include <rapidjson/document.h>
#include <iostream>

bool on = true;

int main (int argc, char *argv[])
{
    int line = 0;
    char ch;
    initscr();
    cbreak();
    noecho();
    //mvaddch(5, 2, 'f');
    refresh();
    while (on)
    {
        ch = getch();
        addch((ch));
        line++;
        if (ch == 27)
        {
            on = false;
        }
    }
    endwin();
	return 0;
}