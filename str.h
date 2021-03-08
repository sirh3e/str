#ifndef STR_H
#define STR_H

#include<sys/types.h>
#include<stdint.h>

typedef uint8_t u8;
typedef size_t  usize;

typedef char*   str;

struct __attribute__ ((__packed__)) str8{
    u8 buffer_allocated;
    u8 buffer_length;
    u8 buffer_flags;
    char buffer[];
};



#endif //STR_H
