#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
salsa.config layout (salsa configurations)
plugin_directory = ~/salsa-plugins



*/

/*
plugin.config layout (plugins)
name = name
version = 0.0.1
enabled = true
exec = ./plugin // interpereted languages will use "python main.py", don't use
interpereted languages

*/

int get_configurations() {
  char *home_path = getenv("HOME");
  char *config_path = calloc(PATH_MAX, sizeof(char));
  sprintf(config_path, "%s/.config", home_path);
  mkdir(config_path, 0777);
  sprintf(config_path, "%s/.config/salsa", home_path);
  mkdir(config_path, 0777);
  /*
      char myString[100];

      while(fgets(myString, 100, fptr)) {
      printf("%s", myString);
      }
  */
  free(config_path);
  config_path = NULL;
  return 0;
}