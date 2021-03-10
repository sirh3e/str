#include <string.h>

#include "str.h"
#include "strlib.h"

str str_from(const char *string){
    usize string_length = strlen(string);

    str self;
    if((self = str_with_capacity(string_length)) == NULL){
        exit(1);
    }

    memcpy(self, string, string_length);
    string[string_length] = '\0';

    str_set_length(self, string_length);

    return self;
}

str str_with_capacity(usize capacity){

    str string;
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

    str_set_type(string, struct_type);
    str_set_capacity(string, string_size);

    return string;
}
