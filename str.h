#ifndef STR_H
#define STR_H

#include<sys/types.h>
#include<stdlib.h>
#include<stdint.h>
#include <stdio.h>

typedef uint8_t u8;
typedef size_t  usize;

typedef char*   str;

#define STR_TYPE_STR8 1
#define STR_TYPE_MASK 7

#define STR_GET(string, type) ((struct str##type *)((string)-(sizeof(struct str##type))))
#define STR_ALLOCATED(string, type) (STR_GET(string, type)->allocated)
#define STR_LENGTH(string, type) (STR_GET(string, type)->length)

struct __attribute__ ((__packed__)) str8{
    u8 allocated;
    u8 length;
    u8 flags;
    char buffer[];
};

static inline u8 str_get_flags(const str string){
    return string == NULL ? 0 : string[-1];
}

static inline void str_set_flags(str string, u8 flags){
    STR_GET(string, 8)->flags = flags;
}

static inline u8 str_get_type(const str string){
    return str_get_flags(string) & STR_TYPE_MASK;
}

static inline void str_set_type(str string, u8 type){
    STR_GET(string, 8)->flags |= type & STR_TYPE_MASK;
}

static inline usize str_get_struct_size(u8 type){
    switch(type){
        case STR_TYPE_STR8:
            return sizeof(struct str8);
    }
    return 0;
}

static inline usize str_get_allocated(const str string){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            return STR_ALLOCATED(string, 8);
    }

    return 0;
}

static inline void str_set_allocated(str string, usize capacity){
    u8 type = str_get_type(string);

    switch(type){
        case STR_TYPE_STR8:
            STR_GET(string, 8)->allocated = capacity;
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
            STR_GET(string, 8)->length = length;
            break;
    }
}

str str_from(const char* source_string);
str str_with_capacity(usize capacity);

void str_free(str string);

#endif //STR_H
