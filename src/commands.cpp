#include <string>
#include <iostream>
#include <rapidjson/document.h>
#include "commands.h"
#include "json_reader.h"

bool ctrl;
bool shift;
bool fn;
bool cmd;
bool capslock;
bool alt;

rapidjson::Document json;

namespace commands
{
    void load_json()
    {
        json = getjson("Salsa/configurations/commands.json");
    }

    void exec_macro (std::string key)
    {
        if (json.IsObject())
        {
            if (json.HasMember("real") && json["real"].IsString())
            {
                std::cout << json["real"].GetString() << std::endl;
            }
        }
    }
}