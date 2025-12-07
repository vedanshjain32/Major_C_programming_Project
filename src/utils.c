#include <string.h>
#include <ctype.h>
#include "utils.h"

int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        unsigned char c1 = tolower((unsigned char)s1[i]);
        unsigned char c2 = tolower((unsigned char)s2[i]);
        if (c1 != c2 || c1 == '\0' || c2 == '\0')
            return c1 - c2;
    }
    return 0;
}

char* my_strcasestr(const char* haystack, const char* needle) {
    if (!*needle) return (char*)haystack;

    size_t nlen = strlen(needle);

    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) ==
            tolower((unsigned char)*needle)) {
            if (strncasecmp(haystack, needle, nlen) == 0)
                return (char*)haystack;
        }
    }
    return NULL;
}

void strip_newline(char *s) {
    size_t len = strlen(s);
    if (len && s[len-1] == '\n')
        s[len-1] = '\0';
}
