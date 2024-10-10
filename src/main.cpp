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
            if (ch == 27) { // escape
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
            } else if (ch == 265) { // f1
                printw("(f1)");
            } else if (ch == 266) { // f2
                printw("(f2)");
            } else if (ch == 267) { // f3
                printw("(f3)");
            } else if (ch == 268) { // f4
                printw("(f4)");
            } else if (ch == 269) { // f5
                printw("(f5)");
            } else if (ch == 270) { // f6
                printw("(f6)");
            } else if (ch == 271) { // f7
                printw("(f7)");
            } else if (ch == 272) { // f8
                printw("(f8)");
            } else if (ch == 273) { // f9
                printw("(f9)");
            } else if (ch == 274) { // f10
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