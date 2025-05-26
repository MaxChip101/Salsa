#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

#include "configs.h"
#include "input.h"
#include "log.h"
#include "renderer.h"

int main() {
  block_interupts();
  if (log_initiate()) {
    printf("salsa: failed to initialize logger\n");
    return 1;
  }

  get_configurations();

  int width, height;
  get_terminal_size(&width, &height);
  Display display = create_display(width, height);
  if (display.sucessful == 0) {
    LOG_ERROR("failed to initialize display");
    printf("salsa: failed to initialize display\n");
    return 1;
  }
  disable_cursor();
  enable_raw_mode();
  create_buffer();

  int posx = 0;
  int posy = 0;

  Widget test = create_widget(0, 0, width / 2, height, 0);
  if (test.sucessful == 0) {
    LOG_ERROR("failed to initialize widget");
    printf("salsa: failed to initialize widget\n");
    return 1;
  }

  if (add_widget(&display, test)) {
    LOG_ERROR("failed to add widget to display");
    printf("salsa: failed to add widget to display\n");
    return 1;
  }

  while (1) {
    render_display(display);
    char key = get_key();
    if (key == 27) {  // escape
      char next = next_key(1000);
      if (next == '[') {
        char next2 = next_key(1000);
        if (next2 == 'A' && posy > 0) {
          LOG_INFO("pressed");
          posy++;
        } else if (next2 == 'B' && posy < height) {
          LOG_INFO("pressed");
          posy--;
        } else if (next2 == 'C' && posx < width) {
          LOG_INFO("pressed");
          posx++;
        } else if (next2 == 'D' && posx > 0) {
          LOG_INFO("pressed");
          posx--;
        }
      } else {
        LOG_INFO("escape");
        break;  // exit
      }
    }
    if (key == '\n' && posy < height) {
      posx = 0;
      posy++;
    } else if (key == 127 && posx > 0) {
      posx--;
      Cell cell = {L'\0', {0, 0, 0}, {255, 255, 255}, ATTRIBUTE_NONE};
      set_cell(&test, posx, posy, cell);
    } else if (posx < width) {
      Cell cell = {(wchar_t)key, {0, 0, 0}, {255, 255, 255}, ATTRIBUTE_BOLD};
      set_cell(&test, posx, posy, cell);

      char *string;
      asprintf(&string, "x:%d, y:%d, w:%d, h:%d", posx, posy, width, height);
      LOG_INFO(string);
      free(string);
      string = NULL;

      posx++;
    }
  }
  original_buffer();
  disable_raw_mode();
  destroy_widget(&test);
  destroy_display(&display);
  endable_cursor();
  log_end();
  return 0;
}
