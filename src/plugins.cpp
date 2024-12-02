#include <iostream>
#include <filesystem>
#include <vector>
#include <dlfcn.h>
#include <ncurses.h>
#include <string>
#include <cstring>
#include "display.h"
#include "plugins.h"
#include "salsa_plugin.h"

Context* getContext(void)
{
    
}

void update_plugins()
{

}

void end_plugins()
{
    
}


void send_key(std::string text, Context context)
{
    for (size_t i = 0; i < text.size(); i++)
    {
        
        if(text[i] == '\0' && i+4 <= text.size())
        {
            std::cout << "utf" << std::endl;
            char _str[4] = {text[i+1], text[i+2], text[i+3], text[i+4]};
            i+=4;
            context.setChar(i, 0, std::string(_str));

        }
        else
        {
            std::cout << "ascii" << std::endl;
            context.setChar(i, 0, std::string(1, text[i]));
        }
    }
    context.render();
    //printw(text); 
}