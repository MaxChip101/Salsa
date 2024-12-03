#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>

struct char4
{

};


class Context
{
public:
    int width, height;
    std::string **display;

    // Constructor to initialize the display
    Context() : width(0), height(0), display(nullptr) {}

    ~Context() 
    {
        if (display != nullptr) {
            for (int i = 0; i < width; i++) {
                delete[] display[i];
            }
            delete[] display;
        }
    }


    void setup(int _width, int _height);
    void setChar(int _col, int _row, std::string _ch);
    void setStr(int _col, int _row, std::string _str);
    std::string getChar(int _col, int _row);
    //char getRenderedChar(int _col, int _row);
    void render();
};

extern Context* current_context;

#endif