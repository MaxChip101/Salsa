#ifndef JSON_READER_H
#define JSON_READER_H

#include <rapidjson/document.h>

rapidjson::Document getjson(const char *file);

#endif