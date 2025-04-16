#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "log.h"

FILE* log_file;

int log_initiate() {
    char* name = calloc(256, sizeof(char));
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);
    sprintf(name, "log/%i-%i-%i-%i-%i-%i.log", 1900 + time_info->tm_year, time_info->tm_mon + 1, 
        time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    log_file = fopen(name, "a");
    free(name);
    return 0;
}

int log_write(char* message) {
    fprintf(log_file, message);
    return 0;
}

int log_end() {
    fclose(log_file);
    return 0;
}