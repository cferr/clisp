#ifndef ENV_H
#define ENV_H
#include <stdlib.h>
#include <stdio.h> //for printf, remove after debug
#include <string.h>

struct val {
    char* identifier;
    void* value;
    size_t type_size;
};

struct env {
    struct val** values;
    unsigned int nb_values;
    struct env* parent; // is this one really useful ? maybe....
    struct env** children;
    unsigned int nb_children;
};

// Maybe we will define hashtables to avoid full tree browsing...
// See this in a close future, when the Lisp interpreter first works, then
// the compiler does its work

typedef struct val val;
typedef struct env env;

/* Value-related functions */

val* create_value(const char* _id, void* _value, const size_t _size);

/* Environments will be handled as trees. Indeed, a variable will either be 
inherited from a parent environment (in which case the lookup function will 
pick the closest one it finds searching from the invocation context), or will 
be declared in the current environment. */

/* Environment-related functions */

env* create_environment();
void append(env* _env, val* _val);
val* lookup(const env* _env, const char* _id);
env* derivate(env* _env);

#endif
