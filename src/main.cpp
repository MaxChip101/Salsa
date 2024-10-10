#include <ncurses.h>
#include <rapidjson/document.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>

// $ Salsa file.txt
// $ Salsa --config
// $ Salsa -c 

void force_stop(int signal) {}

int main (int argc, char *argv[])
{

    signal(SIGINT, force_stop); // block ctrl + c force end
    signal(SIGTSTP, force_stop); // block ctrl + z force end

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
            
            // escape keys
            if (ch == 27) {
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
            } else if (ch == 265) {
                printw("(f1)");
            } else if (ch == 266) {
                printw("(f2)");
            } else if (ch == 267) {
                printw("(f3)");
            } else if (ch == 268) {
                printw("(f4)");
            } else if (ch == 269) {
                printw("(f5)");
            } else if (ch == 270) {
                printw("(f6)");
            } else if (ch == 271) {
                printw("(f7)");
            } else if (ch == 272) {
                printw("(f8)");
            } else if (ch == 273) {
                printw("(f9)");
            } else if (ch == 274) {
                printw("(f10)");
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
            } else {
                addch(char(ch));
            }
        }
    endwin();
    } else {
        std::cerr << "Your terminal does not support coloured text" << std::endl;
        return 1;
    }
	return 0;
}