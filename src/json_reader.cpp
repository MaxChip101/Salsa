#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <string>

// gets a file path and turns it into a json document
rapidjson::Document getjson (const char *file) 
{
    char cwd[1024];
    std::string fullcwd = getcwd(cwd, sizeof(cwd));

    std::cout << fullcwd << std::endl;

    // json file variables
    rapidjson::Document document;
    std::ifstream jsonfile (fullcwd + '/' + file);

    // reading variables
    std::string ln;
    std::string content;

    // checking if file exists
    if (!jsonfile) {
        std::cerr << "Cannot find json file: '" << file << "'" << std::endl;
        exit(1);
    }

    if (!jsonfile.is_open()) {
        std::cerr << "Cannot open json file: '" << file << "'" << std::endl;
        exit(1);
    }

    // reading
    while (getline(jsonfile, ln)) {
        content += ln;
        content.push_back('\n');
    }
    
    // check for errors
    if (document.Parse (content.c_str()).HasParseError())
    {
        std::cerr << "Json file contains errors: '" << file << "'" << std::endl;
        exit(1);
    }
    else
    {
        document.Parse (content.c_str());
    }
    
    return document;
}