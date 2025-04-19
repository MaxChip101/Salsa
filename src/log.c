#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "log.h"

FILE* log_file;

int log_initiate() {
    char* name = calloc(PATH_MAX, sizeof(char));
    if (name == NULL) {
        return 1;
    }

    time_t now = time(NULL);

    struct stat sb;

    if(stat("/tmp/salsa", &sb) != 0 && S_ISDIR(sb.st_mode)) {
        mkdir("/tmp/salsa", 0777);
    }
    
    if(stat("/tmp/salsa/log", &sb) != 0 && S_ISDIR(sb.st_mode)) {
        mkdir("/tmp/salsa/log", 0777);
    }

    struct tm* time_info = localtime(&now);
    sprintf(name, "/tmp/salsa/log/salsa-%i-%02d-%02d_%02d-%02d-%02d.log", 1900 + time_info->tm_year, time_info->tm_mon + 1, 
        time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
    log_file = fopen(name, "a");
    
    free(name);
    return 0;
}

int log_write(char* message, char* level, char* source) {
    time_t now = time(NULL);
    struct tm* time_info = localtime(&now);

    fprintf(log_file, "[%i-%02d-%02d %02d:%02d:%02d] [%s] [%s]\t%s\n", 1900 + time_info->tm_year, time_info->tm_mon + 1, 
        time_info->tm_mday, time_info->tm_hour, time_info->tm_min, time_info->tm_sec, level, source, message);
    return 0;
}

int log_end() {
    fclose(log_file);
    return 0;
}