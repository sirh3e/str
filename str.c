#include <assert.h>
#include <string.h>

#include "str.h"
#include "strlib.h"

void str_clear(str self){
    assert(self);
    
    memset(self, 0, str_get_length(self));
    str_set_length(self, 0);
}

int str_is_empty(const str self){
    assert(self);
    
    return str_get_length(self) == 0;
}

str str_from(const char *string){
    assert(string);
    
    str self;
    usize string_length = strlen(string);
    if((self = str_with_capacity(string_length)) == NULL){
        assert(self);
    }

    memcpy(self, string, string_length);
    self[string_length] = '\0';

    str_set_length(self, string_length);

    return self;
}

str str_with_capacity(usize capacity){

    str self;
    u8 struct_type = STR_TYPE_STR8;
    usize struct_size = str_get_struct_size(struct_type);
    usize string_size = sizeof(char) * capacity + 1;
    usize malloc_size = struct_size + string_size;

    void *ptr;
    if((ptr = str_malloc(malloc_size)) == NULL){
        exit(1); //ToDo find a better way
    }

    memset(ptr, 0, malloc_size);
    self = (str)ptr+struct_size;

    str_set_type(self, struct_type);
    str_set_capacity(self, string_size);

    return self;
}
