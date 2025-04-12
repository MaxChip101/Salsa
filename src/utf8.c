#include <stdlib.h>

#include "utf8.h"

UTF8 create_utf(char* str, int size) {
    UTF8 utf8 = {str, size};
    return utf8;
}

UTF8 char_to_utf8(char ch) {
    int size = 5;
    char* utf8_value = calloc(size, sizeof(char));
    if(utf8_value == NULL) {
        UTF8 err = {NULL, 0};
        return err;
    }
    utf8_value[0] = ch;
    UTF8 utf8 = {utf8_value, size};
    return utf8;
}
