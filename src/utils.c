#include <stdio.h>
#include "utils.h"


void clear_input_buffer() {
int c;
while ((c = getchar()) != '\n' && c != EOF) {}
}

void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len && s[len-1] == '\n')
        s[len-1] = '\0';
}
