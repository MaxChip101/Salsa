#include <ncurses.h>

int cwidth, cheight;
char **character_display;

namespace display
{
    void setup(int width, int height)
    {
        cwidth = width;
        cheight = height;
        for (int i = 0; i < cwidth; i++) {
            character_display[i] = new char[cheight];
        }
    }

    void setChar(int line, int char_pos, char character)
    {
        character_display[char_pos][char_pos] = character;
    }

    void draw()
    {
        clear();
        for (int x = 0; x < cwidth; x++)
        {
            for (int y = 0; y < cheight; y++)
            {
                addch(character_display[x][y]);
            }
        }
    }

}