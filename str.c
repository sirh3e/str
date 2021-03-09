#include "str.h"
#include "strlib.h"

#include<string.h>

static inline usize str_get_struct_size(u8 type){
    switch(type){
        case STR_TYPE_STR8:
            return sizeof(struct str8);
    }
    return 0;
}

str str_with_capacity(usize capacity){

    str string;
    str name = "marvin";
    usize name_length = strlen(name);
    u8 struct_type = STR_TYPE_STR8;
    usize struct_size = str_get_struct_size(struct_type);
    usize string_size = sizeof(char) * capacity + 1;
    usize malloc_size = struct_size + string_size;

    void *ptr;
    if((ptr = str_malloc(malloc_size)) == NULL){
        exit(1);
    }

    memset(ptr, 0, malloc_size);
    string = (str)ptr+struct_size;

    memcpy(string, name, name_length);
    string[name_length] = '\0';

    str_set_allocated(string, string_size);
    str_set_length(string, name_length);
    str_set_flags(string, struct_type);

    return string;
}
