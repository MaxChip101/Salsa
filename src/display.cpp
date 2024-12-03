#include <ncurses.h>
#include <string>
#include "display.h"

void Display_Context::setup(int _width, int _height)
{
    Display_Context::width = _width;
    Display_Context::height = _height;

    Display_Context::display = new std::string*[height];
    for (int i = 0; i < height; i++)
    {
        Display_Context::display[i] = new std::string[width];
    }
}

void Display_Context::setChar(int _col, int _row, std::string _ch)
{
    if(_col < Display_Context::width && _col >= 0 && _row < Display_Context::height && _row >= 0)
    {
        Display_Context::display[_row][_col] = _ch;
    }
}

void Display_Context::setStr(int _col, int _row, std::string _str)
{
    size_t i = 0;
    while (i < _str.size())
    {
        unsigned char lead = static_cast<unsigned char>(_str[i]);
        size_t char_len = 1;
        if (lead < 0x80)
        {
            char_len = 1; // 1 byte ASCII char
        }
        else if ((lead & 0xE0) == 0xC0)
        {
            char_len = 2; // 2 byte UTF-8 char
        }
        else if ((lead & 0xF0) == 0xE0) {
            char_len = 3; // 3 byte UTF-8 char
        }
        else if ((lead & 0xF8) == 0xF0) {
            char_len = 4; // 4 byte UTF-8 char
        }
        else
        {
            break; // invalid UTF-8 char
        }

        if (i + char_len > _str.size())
        {
            break; // incomplete UTF-8 char
        }

        std::string ch = _str.substr(i, char_len);
        Display_Context::setChar(_col + i, _row, ch);

        i += char_len;
    }
}

std::string Display_Context::getChar(int _col, int _row)
{
    if(_col < Display_Context::width && _col >= 0 && _row < Display_Context::height && _row >= 0)
    {
        return Display_Context::display[_col][_row];
    }
    return "\0";
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
void Display_Context::render()
{
    clear();
    for (int x = 0; x < Display_Context::width; x++)
    {
        for (int y = 0; y < Display_Context::height; y++)
        {
            if (!Display_Context::display[y][x].empty())
            {
                mvprintw(y, x, Display_Context::display[y][x].c_str());
            }
        }
    }
    refresh();
}