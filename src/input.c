#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int start_input()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    return(0);
}

char get_key()
{
    char c;
    if(read(STDIN_FILENO, &c, 1) == 1)
    {
        return(c);
    }
    else
    {
        return('\0');
    }
}

int end_input()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    return(0);
}