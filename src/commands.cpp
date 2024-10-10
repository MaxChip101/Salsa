#include <ncurses.h>
#include "commands.h"
#include <signal.h>

bool ctrl;
bool shift;
bool fn;
bool cmd;
bool capslock;
bool alt;

namespace commands
{

    Command_Return prompt_command()
    {
        Command_Return cr;
        cr.cmd_name = "null";
        cr.content = "null";
        return cr;
    }

    Command_Return macro_command()
    {
        Command_Return cr;
        cr.cmd_name = "null";
        cr.content = "null";
        return cr;
    }
}