#ifndef PARSER_H
#define PARSER_H
#include "env.h"
#include "common.h"
#include <stdio.h>

#define STAT_NORMAL 0
#define STAT_STR 1
#define IGNORE 2

// Recursive function, reursive calls happen when encoutering 
// parentheses
void parse(const char* _str, env* _curEnv, bufword** _buf, int _len, 
           unsigned int* _seek);

#endif
