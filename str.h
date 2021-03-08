#ifndef STR_H
#define STR_H

#include<stdint.h>

typedef uint8_t u8;

typedef char* str;

struct __attribute__ ((__packed__)) str8{
    u8 buffer_allocated;
    u8 buffer_length;
    u8 buffer_flags;
    char buffer[];
};

#endif //STR_H
