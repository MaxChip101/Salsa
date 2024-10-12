#ifndef DISPLAY_H
#define DISPLAY_H

namespace display
{
    void setup(int width, int height);
    void setChar(int line, int character_pos, char character);
    void draw();
}

#endif