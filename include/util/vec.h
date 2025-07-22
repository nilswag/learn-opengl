#pragma once
#include "defines.h"
#include "log.h"
#include <stdlib.h>
#include <string.h>

#define VEC_DEFAULT_SIZE 8
#define VEC_GROW_FACTOR 2

// =============================================================================================================================================== \\

#define VEC_TYPE(name, type)                                                                                                                        \
    typedef struct {                                                                                                                                \
        type* data;                                                                                                                                 \
        size_t size;                                                                                                                                \
        size_t capacity;                                                                                                                            \
    } vec_##name##_t;                                                                                                                               \

#define vec(name) vec_##name##_t

// =============================================================================================================================================== \\

#define VEC_PROTOTYPES(scope, name, type)                                                                                                           \
    scope bool vec_##name##_init(vec(name)* vec);                                                                                                   \
    scope void vec_##name##_destroy(vec(name)* vec);                                                                                                \
                                                                                                                                                    \
    scope void vec_##name##_clear(vec(name)* vec);                                                                                                  \
                                                                                                                                                    \
    scope bool vec_##name##_resize(vec(name)* vec, size_t new_capacity);                                                                            \
    scope bool vec_##name##_pushAt(vec(name)* vec, size_t index, type el);                                                                          \
    scope bool vec_##name##_popAt(vec(name)* vec, size_t index, type* out);                                                                         \
                                                                                                                                                    \
    scope bool vec_##name##_pushBack(vec(name)* vec, type el);                                                                                      \
    scope bool vec_##name##_pushFront(vec(name)* vec, type el);                                                                                     \
    scope bool vec_##name##_popBack(vec(name)* vec, type* out);                                                                                     \
    scope bool vec_##name##_popFront(vec(name)* vec, type* out);                                                                                    \

// =============================================================================================================================================== \\

#define VEC_IMPL(scope, name, type)                                                                                                                 \
    scope bool vec_##name##_init(vec(name)* vec)                                                                                                    \
    {                                                                                                                                               \
        memset(vec, 0, sizeof(vec(name)));                                                                                                          \
                                                                                                                                                    \
        vec->data = calloc(1, VEC_DEFAULT_SIZE * sizeof(type));                                                                                     \
        if (!vec->data)                                                                                                                             \
        {                                                                                                                                           \
            LOG_ERROR("Unable to allocate memory for vector of type %s.", #name);                                                                   \
            return false;                                                                                                                           \
        }                                                                                                                                           \
                                                                                                                                                    \
        vec->capacity = VEC_DEFAULT_SIZE;                                                                                                           \
        return true;                                                                                                                                \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope void vec_##name##_destroy(vec(name)* vec)                                                                                                 \
    {                                                                                                                                               \
        free(vec->data);                                                                                                                            \
        memset(vec, 0, sizeof(vec(name)));                                                                                                          \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope void vec_##name##_clear(vec(name)* vec)                                                                                                   \
    {                                                                                                                                               \
        memset(vec->data, 0, vec->size * sizeof(type));                                                                                             \
        vec->size = 0;                                                                                                                              \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_resize(vec(name)* vec, size_t new_capacity)                                                                             \
    {                                                                                                                                               \
        if (new_capacity < vec->size)                                                                                                               \
        {                                                                                                                                           \
            LOG_ERROR("Unable to resize vector because new capacity is smaller than the current size, %zu < %zu", new_capacity, vec->size);         \
            return false;                                                                                                                           \
        }                                                                                                                                           \
                                                                                                                                                    \
        type* new_data = realloc(vec->data, new_capacity * sizeof(type));                                                                           \
        if (!new_data)                                                                                                                              \
        {                                                                                                                                           \
            LOG_ERROR("Unable to allocate memory for vector of type %s.", #name);                                                                   \
            return false;                                                                                                                           \
        }                                                                                                                                           \
        vec->data = new_data;                                                                                                                       \
        vec->capacity = new_capacity;                                                                                                               \
                                                                                                                                                    \
        return true;                                                                                                                                \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_pushAt(vec(name)* vec, size_t index, type el)                                                                           \
    {                                                                                                                                               \
        if (index > vec->size)                                                                                                                      \
        {                                                                                                                                           \
            LOG_ERROR("Unable to push element since index is out of bounds for index: %zu.", index);                                                \
            return false;                                                                                                                           \
        }                                                                                                                                           \
                                                                                                                                                    \
        if (vec->size == vec->capacity)                                                                                                             \
        {                                                                                                                                           \
            if (!vec_##name##_resize(vec, vec->capacity * VEC_GROW_FACTOR))                                                                         \
            {                                                                                                                                       \
                LOG_ERROR("Unable to resize vector.");                                                                                              \
                return false;                                                                                                                       \
            }                                                                                                                                       \
        }                                                                                                                                           \
                                                                                                                                                    \
        memmove(&vec->data[index + 1], &vec->data[index], (vec->size - index) * sizeof(type));                                                      \
                                                                                                                                                    \
        vec->data[index] = el;                                                                                                                      \
        vec->size++;                                                                                                                                \
                                                                                                                                                    \
        return true;                                                                                                                                \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_popAt(vec(name)* vec, size_t index, type* out)                                                                          \
    {                                                                                                                                               \
        if (index >= vec->size)                                                                                                                     \
        {                                                                                                                                           \
            LOG_ERROR("Unable to pop element since index is out of bounds for index: %zu.", index);                                                 \
            return false;                                                                                                                           \
        }                                                                                                                                           \
                                                                                                                                                    \
        *out = vec->data[index];                                                                                                                    \
        memmove(&vec->data[index], &vec->data[index + 1], (vec->size - index - 1) * sizeof(type));                                                  \
                                                                                                                                                    \
        vec->size--;                                                                                                                                \
                                                                                                                                                    \
        return true;                                                                                                                                \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_pushBack(vec(name)* vec, type el)                                                                                       \
    {                                                                                                                                               \
        return vec_##name##_pushAt(vec, vec->size, el);                                                                                             \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_pushFront(vec(name)* vec, type el)                                                                                      \
    {                                                                                                                                               \
        return vec_##name##_pushAt(vec, 0, el);                                                                                                     \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_popBack(vec(name)* vec, type* out)                                                                                      \
    {                                                                                                                                               \
        return vec_##name##_popAt(vec, vec->size - 1, out);                                                                                         \
    }                                                                                                                                               \
                                                                                                                                                    \
    scope bool vec_##name##_popFront(vec(name)* vec, type* out)                                                                                     \
    {                                                                                                                                               \
        return vec_##name##_popAt(vec, 0, out);                                                                                                     \
    }