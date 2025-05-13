#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <signal.h>

void interupt(int)
{
}

void stop(int)
{
}

void block_interupts()
{
    signal(SIGINT, interupt);
    signal(SIGTSTP, stop);
}

int enable_raw_mode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    return 0;
}

char get_key()
{
    char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
    {
        return c;
    }
    else
    {
        return L'\0';
    }
}

char next_key(int timeout)
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = timeout;

    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);

    if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0)
    {
        char c;
        read(STDIN_FILENO, &c, 1);
        return c;
    }
    else
    {
        return '\0';
    }
}

int disable_raw_mode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    return 0;
}