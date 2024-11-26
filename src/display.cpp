#include <ncurses.h>
#include "display.h"


Context::setup(int _width, int _height)
{
    Context::width = _width;
    Context::height = _height;
    for (int i = 0; i < Context::width; i++) {
        Context::display[i] = new char[Context::height];
    }
}

Context::setChar(int _col, int _row, char _ch)
{
    Context::display[_col][_row] = _ch;
}

Context::getChar(int _col, int _row)
{
    if(_col <= Context::width && _col >= 0 && _row <= Context::height && _row >= 0)
    {
        return Context::display[_col, _row];
    }
}

Context::getRenderedChar(int _col, int _row)
{
    if(_col <= Context::width && _col >= 0 && _row <= Context::height && _row >= 0)
    {
        return mvinch(_row, _col);
    }
}

Context::render()
{
    clear();
    for (int x = 0; x < Context::width; x++)
    {
        for (int y = 0; y < Context::height; y++)
        {
            mvaddch(y, x, Context::display[x][y]);
        }
    }
}