#ifndef PLUGIN_H
#define PLUGIN_H

typedef struct {
  const char* name;
} Plugin;

void start_event();
void display_resize_event(int width, int height);
void quit_event();

#endif