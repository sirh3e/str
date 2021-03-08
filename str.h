#ifndef STR_H
#define STR_H

#include<sys/types.h>
#include<stdint.h>

typedef uint8_t u8;
typedef size_t  usize;

typedef char*   str;

#define STR_TYPE_STR8 1
#define STR_TYPE_MASK 7

#define STR_GET(string, type) ((struct str##type *)((string)-(sizeof(struct str##type))))
#define STR_GET_LENGTH(string, type) (STR_GET(string, type)->buffer_length)

struct __attribute__ ((__packed__)) str8{
    u8 buffer_allocated;
    u8 buffer_length;
    u8 flags;
    char buffer[];
};

static inline usize str_get_length(const str string){
    u8 flags = string[-1];

    switch(flags & STR_TYPE_MASK){
        case STR_TYPE_STR8:
            return STR_GET_LENGTH(string, 8);
    }

    return 0;
}

#endif //STR_H
