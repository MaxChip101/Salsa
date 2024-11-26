#ifndef PLUGINS_H
#define PLUGINS_H

#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Salsa_Plugin {
    const char* name;
    void (*init)(void);
    void (*update)(void);
    void (*input)(const char* text);
    void (*end)(void);
};

Context getContext(void);

int getnum(void);

#ifdef __cplusplus
}
#endif


#endif
