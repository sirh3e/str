#include "str.h"
#include "strlib.h"

#include<string.h>

str str_from(const char *source_string){
    usize string_length = strlen(source_string);

    str string;
    if((string = str_with_capacity(string_length)) == NULL){
        exit(1);
    }

    memcpy(string, source_string, string_length);
    string[string_length] = '\0';

    str_set_length(string, string_length);

    return string;
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
    str_set_allocated(string, string_size);

    return string;
}
