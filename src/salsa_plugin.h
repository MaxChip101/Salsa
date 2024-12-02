#ifndef SALSA_PLUGIN_H
#define SALSA_PLUGIN_H

struct Salsa_Plugin
{
    const char* name;
    void (*init)(void);
    void (*update)(void);
    void (*input)(const char* text);
    void (*end)(void);
};

#endif