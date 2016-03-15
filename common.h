#ifndef COMMON_H
#define COMMON_H
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define BASE_ALLOCATION_LENGTH 16

struct bufword {
    char* wd;
    unsigned int len;
    unsigned int allocd_len;
    struct bufword* next;
};

typedef struct bufword bufword;

// functions on words

bufword* new_bufword();
bufword* bufword_appendc(bufword* _buf, char c);
bufword* bufword_froms(bufword* _buf, const char* _s, int _len);

#endif
