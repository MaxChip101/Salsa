#ifndef INPUT_H
#define INPUT_H


int enable_raw_mode();
char get_key();
char next_key(int timeout);
int disable_raw_mode();

#endif