#ifndef PLUGINS_H
#define PLUGINS_H

#include <string>
#include "display.h"

#ifdef __cplusplus
extern "C" {
#endif

void load_plugins();
void end_plugins();
void send_key(std::string text);

Display_Context* getContext(void);

#ifdef __cplusplus
}
#endif


#endif
