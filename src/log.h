#ifndef LOG_H
#define LOG_H

#define LOG_INFO(message) log_write((message), "INFO", __FILE__, __func__)
#define LOG_DEBUG(message) log_write((message), "DEBUG", __FILE__, __func__)
#define LOG_WARN(message) log_write((message), "WARN", __FILE__, __func__)
#define LOG_ERROR(message) log_write((message), "ERROR", __FILE__, __func__)

int log_initiate();
int log_write(char *message, char *level, const char *source, const char *context);
int log_end();

#endif