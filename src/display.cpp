#include <ncurses.h>
#include "display.h"


void Context::setup(int _width, int _height)
{
    Context::width = _width;
    Context::height = _height;
    for (int i = 0; i < Context::width; i++) {
        Context::display[i] = new char[Context::height];
    }
}

void Context::setChar(int _col, int _row, char _ch)
{
    Context::display[_col][_row] = _ch;
}

char Context::getChar(int _col, int _row)
{
    if(_col <= Context::width && _col >= 0 && _row <= Context::height && _row >= 0)
    {
        return Context::display[_col][_row];
    }
    return -1;
}

char Context::getRenderedChar(int _col, int _row)
{
    if(_col <= Context::width && _col >= 0 && _row <= Context::height && _row >= 0)
    {
        return mvinch(_row, _col);
    }
    return -1;
}

void Context::render()
{
    clear();
    for (int x = 0; x < Context::width; x++)
    {
        for (int y = 0; y < Context::height; y++)
        {
            mvaddch(y, x, Context::display[x][y]);
        }
    }
    refresh();
}