#ifndef __LINEINPUT_H
#define __LINEINPUT_H
#include <stdint.h>

// forward declarations
uint8_t linput_readline(uint8_t *, unsigned int);
void    linput_init();
void    completion(const char *, linenoiseCompletions *);
char *  hints(const char *, int *color, int *);
void    linput_save();

#endif

