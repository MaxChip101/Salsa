#include <ncurses.h>
#include <string>
#include "display.h"

void Context::setup(int _width, int _height)
{
    Context::width = _width;
    Context::height = _height;

    Context::display = new std::string*[height];
    for (int i = 0; i < height; i++)
    {
        Context::display[i] = new std::string[width];
    }
}

void Context::setChar(int _col, int _row, std::string _ch)
{
    if(_col < Context::width && _col >= 0 && _row < Context::height && _row >= 0)
    {
        Context::display[_row][_col] = _ch;
    }
}

std::string Context::getChar(int _col, int _row)
{
    if(_col < Context::width && _col >= 0 && _row < Context::height && _row >= 0)
    {
        return Context::display[_col][_row];
    }
    return "\0\0\0\0";
}
/*
char Context::getRenderedChar(int _col, int _row)
{
    if(_col <= Context::width && _col >= 0 && _row <= Context::height && _row >= 0)
    {
        return mvinch(_row, _col);
    }
    return -1;
}
*/
void Context::render()
{
    clear();
    for (int x = 0; x < Context::width; x++)
    {
        for (int y = 0; y < Context::height; y++)
        {
            if (!Context::display[y][x].empty())
            {
                //std::string _str = "(" + Context::display[y][x] + ")";
                //mvprintw(y, x*_str.size()+1, _str.c_str());
                mvprintw(y, x, Context::display[y][x].c_str());
            }
        }
    }
    refresh();
}