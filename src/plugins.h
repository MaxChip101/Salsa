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

void load_plugins(const std::string& plugin_dir);
void end_plugins();
void send_key(const char* text);

Context* getContext(void);
void destroyContext(Context* context);

#ifdef __cplusplus
}
#endif


#endif
