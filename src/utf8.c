#include <stdlib.h>

#include "utf8.h"

char* char_to_utf8(char ch) {
    char* utf8_char = calloc(5, sizeof(char));
    utf8_char[0] = ch;
    return utf8_char;
}
