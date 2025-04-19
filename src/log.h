#ifndef LOG_H
#define LOG_H

int log_initiate();
int log_write(char* message, char* level, char* source);
int log_end();

#endif