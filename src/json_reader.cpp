#include <rapidjson/document.h>
#include <fstream>
#include <iostream>
#include <string>

rapidjson::Document getjson(const char *file) {

    // json file variables
    rapidjson::Document document;
    std::ifstream jsonfile(file);

    // reading variables
    std::string ln;
    std::string content;

    // checking if file exists
    if (!jsonfile.is_open()) {
        std::cerr << "Cannot find JSON file: '" << file << "'" << std::endl;
        exit(1);
    }

    // reading
    while(getline(jsonfile, ln)) {
        content += ln;
        content.push_back('\n');
    }
    
    // check for errors
    if(document.Parse(content.c_str()).HasParseError()) {
        std::cerr << "JSON file contains errors: '" << file << "'" << std::endl;
    }

    // return
    document.Parse(content.c_str());
    return document;
}