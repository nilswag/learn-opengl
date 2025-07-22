#pragma once
#include "defines.h"
#include "log.h"
#include <stdlib.h>

#define VEC_DEFAULT_SIZE 8
#define VEC_GROW_FACTOR 2

#define VEC_TYPE(name, type)                                                    \
    typedef struct {                                                            \
        type* data;                                                             \
        size_t size;                                \
        size_t capacity;                            \
    } vec_##name##_t;                               \

#define vec(name) vec_##name##_t

#define VEC_PROTOTYPES(scope, name, type)   \
    scope bool vec_##name##_init(vec(name)* vec); \
    scope void vec_##name##_destroy(vec(name)* vec); \
\
    scope void vec_##name##_clear(vec(name)* vec);\
\
    scope bool vec_##name##_resize(vec(name)* vec, size_t new_capacity);\
    scope bool vec_##name##_pushAt(vec(name)* vec, size_t index, type el);\
    scope bool vec_##name##_popAt(vec(name)* vec, size_t index, type* out);\
\
    scope bool vec_##name##_pushBack(vec(name)* vec, type el);\
    scope bool vec_##name##_pushFront(vec(name)* vec, type el);\
    scope bool vec_##name##_popBack(vec(name)* vec, type* out);\
    scope bool vec_##name##_popFront(vec(name)* vec, type* out);\

#define VEC_IMPL(scope, name, type)\
    scope bool vec_##name##_init(vec(name)* vec)\
    {\
        memset(vec, 0, sizeof(vec(name)));\
\
        vec->data = calloc(1, VEC_DEFAULT_SIZE * sizeof(type));\
        if (!vec->data)\
        {\
            LOG_ERROR("Unable to allocate memory for vector of type %s.", #name);\
            return false;\
        }\
\
        vec->capacity = VEC_DEFAULT_SIZE;\
        return true;\
    }\
\
scope void vec_##name##_destroy(vec(name)* vec)\
{\
    free(vec->data);\
    memset(vec, 0, sizeof(vec(name)));\
}\
\
scope void vec_##name##_clear(vec(name)* vec)\
{\
    memset(vec->data, 0, vec->size * sizeof(type));\
    vec->size = 0;\
}\