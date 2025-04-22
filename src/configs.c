#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <linux/limits.h>

int get_configurations() {
    char *home_path = getenv("HOME");
    char *config_path = calloc(PATH_MAX, sizeof(char));
    sprintf(config_path, "%s/.config", home_path);
    mkdir(config_path, 0777);
    sprintf(config_path, "%s/.config/salsa", home_path);
    mkdir(config_path, 0777);

}