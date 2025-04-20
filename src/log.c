#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "log.h"

char* path;

int log_initiate() {
    path = calloc(PATH_MAX, sizeof(char));
    if (path == NULL) {
        return 1;
    }

    time_t now = time(NULL);

    mkdir("/tmp/salsa", 0777);
    mkdir("/tmp/salsa/log", 0777);

    struct tm* time_info = localtime(&now);
    sprintf(path, "/tmp/salsa/log/salsa-%i-%02d-%02d_%02d-%02d-%02d.log", 1900 + time_info->tm_year, time_info->tm_mon + 1, 
        time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
        FILE* log_file = fopen(path, "w");
    fclose(log_file);
    return 0;
}

int log_write(char* message, char* level, char* source) {
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);

    FILE* log_file = fopen(path, "a");
    fprintf(log_file, "[%i-%02d-%02d %02d:%02d:%02d] [%s] [%s]\t%s\n", 1900 + time_info->tm_year, time_info->tm_mon + 1, 
        time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec, level, source, message);
    fclose(log_file);
    return 0;
}

int log_end() {
    free(path);
    return 0;
}