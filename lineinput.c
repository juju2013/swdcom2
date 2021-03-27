// Use Linenoise input from console
#ifdef USE_LINENOISE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include "linenoise/linenoise.h"

#define MAX_HISTORY 2000
const char *SWD_HISTORY  = ".swd.history";
char * line;



void completion(const char *buf, linenoiseCompletions *lc) {
    if (buf[0] == 'h') {
        linenoiseAddCompletion(lc,"hello");
        linenoiseAddCompletion(lc,"hello there");
    }
}

char *hints(const char *buf, int *color, int *bold) {
    if (!strcasecmp(buf,"hello")) {
        *color = 35;
        *bold = 0;
        return " World";
    }
    return NULL;
}


void    linput_init() {
  linenoiseSetCompletionCallback(completion);
  linenoiseSetHintsCallback(hints);
  linenoiseSetMultiLine(1);
  linenoiseHistoryLoad(SWD_HISTORY);
  linenoiseHistorySetMaxLen(MAX_HISTORY);
}

uint8_t linput_readline(uint8_t*buffer, unsigned int buffer_size) {
  
  if (line) {
    free(line);
    line = NULL;
  }
  line = linenoise("input> ");
  if (line) {
    linenoiseHistoryAdd(line);
    // reuse the fixed buffer, reserv latest 2 bytes for \n and 0
    strncpy((char*)buffer, line, buffer_size-2);
    buffer[buffer_size-1]=0;
    unsigned int len = strlen((char*)buffer);
    buffer[len]='\n'; // inject newline
    return len+1;
  }
  // empty line
  buffer[0]=0;
  return 0;
}

void linput_save() {
  linenoiseHistorySave(SWD_HISTORY);
}

#endif
