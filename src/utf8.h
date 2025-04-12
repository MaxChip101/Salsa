#ifndef TEXT_H
#define TEXT_H

typedef struct {
    char* value;
    int size;
} UTF8;

UTF8 create_utf(char* str, int size);
UTF8 char_to_utf8(char ch);

#endif
