#ifndef STR_H
#define STR_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

typedef uint8_t u8;
typedef size_t  usize;

typedef char*   str;

#define STR_TYPE_STR8 1
#define STR_TYPE_MASK 7

#define STR(string, type) ((struct str##type *)((string)-(sizeof(struct str##type))))

#define STR_CAPACITY(string, type) (STR(string, type)->capacity)
#define STR_LENGTH(string, type) (STR(string, type)->length)
#define STR_FLAGS(string, type) (STR(string, type)->flags)

struct __attribute__ ((__packed__)) str8{
    u8 capacity;
    u8 length;
    u8 flags;
    char buffer[];
};

static inline u8 str_get_flags(const str string){
    return string == NULL ? 0 : string[-1];
}

static inline void str_set_flags(str string, u8 flags){
    STR_FLAGS(string, 8) = flags;
}

static inline void str_apply_flags(str string, u8 flags){
    STR_FLAGS(string, 8) |= flags;
}

static inline u8 str_get_type(const str string){
    return str_get_flags(string) & STR_TYPE_MASK;
}

static inline void str_set_type(str string, u8 type){
    str_apply_flags(string, type & STR_TYPE_MASK);
}

static inline usize str_get_struct_size(u8 type){
    switch(type){
        case STR_TYPE_STR8:
            return sizeof(struct str8);
    }
    return 0;
}

static inline usize str_get_capacity(const str string){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            return STR_CAPACITY(string, 8);
    }

    return 0;
}

static inline void str_set_capacity(str string, usize capacity){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            STR_CAPACITY(string, 8) = capacity;
            break;
    }
}

static inline usize str_get_length(const str string){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            return STR_LENGTH(string, 8);
    }

    return 0;
}

static inline void str_set_length(str string, usize length){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            STR_LENGTH(string, 8) = length;
            break;
    }
}

str str_from(const char* source_string);
str str_with_capacity(usize capacity);

void str_free(str string);

#endif //STR_H
