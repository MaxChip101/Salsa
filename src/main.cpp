#include <ncurses.h>
#include <rapidjson/document.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>

#include "commands.h"
#include "display.h"

// $ Salsa file.txt
// $ Salsa --config
// $ Salsa -c 

void ctrl_c(int signal)
{
    printw("(ctrl C)");
    refresh();
}

void ctrl_z(int signal){
    printw("(ctrl Z)");
    refresh();
}

int main (int argc, char *argv[])
{

    commands::load_json();
    commands::exec_macro("real");

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
            ch = getch();

            commands::exec_macro(ch);
            

            if (ch >= 1 && ch <= 26) // ctrl a-z
            { 
                printw("(ctrl %c%c", ch+64, ')');
            }
            else if (ch == 27) { // escape
                printw("(escape)");
                on = false;
            } else if (ch == KEY_UP) {
                printw("(up)");
            } else if (ch == KEY_DOWN) {
                printw("(down)");
            } else if (ch == KEY_LEFT) {
                printw("(left)");
            } else if (ch == KEY_RIGHT) {
                printw("(right)");
            } else if (ch == KEY_BACKSPACE) {
                printw("(backspace)");
            } else if (ch == KEY_HOME) {
                printw("(home)");
            } else if (ch == KEY_END) {
                printw("(end)");
            } else if (ch == KEY_PPAGE) {
                printw("(page up)");
            } else if (ch == KEY_NPAGE) {
                printw("(page down)");
            } else if (ch >= 265 && ch <= 274) { // f1-f10
                printw("(f%d)", ch - 264);
            } else if (ch == KEY_DC) {
                printw("(del)");
            } else if (ch == KEY_IC) {
                printw("(insert)");
            } else if (ch == KEY_SF) {
                printw("(scroll down)");
            } else if (ch == KEY_SR) {
                printw("(scroll up)");
            } else if (ch == KEY_A1) {
                printw("(home 1)");
            } else if (ch == KEY_A3) {
                printw("(home 2)");
            } else if (ch == KEY_C1) {
                printw("(end 1)");
            } else if (ch == KEY_C3) {
                printw("(end 2)");
            } else { // other
                addch(char(ch));
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