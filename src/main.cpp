#include <ncurses.h>

int main(int argc, char *argv[]) {
    initscr();            // Start ncurses mode
    printw("Hello, ncurses on Arch!");  // Print to screen
    refresh();            // Refresh screen to show output
    getch();              // Wait for key press
    endwin();             // End ncurses mode
    return 0;
}