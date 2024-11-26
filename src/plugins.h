#ifndef PLUGINS_H
#define PLUGINS_H

#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

struct Salsa_Plugin
{
    const char* name;
    void (*init)(void);
    void (*update)(void);
    void (*input)(const char* text);
    void (*end)(void);
};

void end_plugins();
void send_key(const char* text);

Context* getContext(void);

#ifdef __cplusplus
}
#endif


#endif
