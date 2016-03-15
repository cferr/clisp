#include "env.h"


val* create_value(const char* _id, void* _value, const size_t _size) {
    val* new = (val*)malloc(sizeof(val));
    unsigned int id_len = strlen(_id);
    new->identifier = (char*)malloc((1 + id_len) * sizeof(char));
    strncpy(new->identifier, _id, id_len);
    new->value = _value;
    new->type_size = _size;
    
    return new;
}

env* create_environment() {
    printf("New environment !\n");
    env* new = (env*)malloc(sizeof(env));
    new->values = NULL;
    new->nb_values = 0;
    new->parent = NULL;
    new->children = NULL;
    new->nb_children = 0;
    
    return new;
}

void append(env* _env, val* _val) {
    if(!_env)
        return;
    // inefficient, but should work
    _env->nb_values++;
    _env->values = (val**)realloc(_env->values, _env->nb_values * sizeof(val*));
    _env->values[_env->nb_values - 1] = _val;
}

val* lookup(const env* _env, const char* _id) {
    if(!_env)
        return NULL;
    
    // look in our values
    int i = 0;
    for(; i < _env->nb_values; i++)
    {
        if(strcmp(_env->values[i]->identifier, _id) == 0)
            return _env->values[i];
    }
    
    // look upwards
    val* ret;
    if(ret = lookup(_env->parent, _id))
        return ret;
    
    return NULL;
}

env* derivate(env* _env) {
    env* new = create_environment();
    new->parent = _env;
    
    if(_env) {
        _env->nb_children++;
        _env->children = (env**)realloc(_env->children, _env->nb_children * \
            sizeof(env*));
        _env->children[_env->nb_children - 1] = new;
    }
    
    return new;
}
