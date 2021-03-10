#include <assert.h>
#include <string.h>

#include "str.h"
#include "strlib.h"

#define ASSERT(expression) \
    assert(expression)

int helper_is_char_boundry(str self, usize index);

int helper_is_char_boundry(str self, usize index){
    ASSERT(self);

    return index <= str_get_length(self);
}

void str_clear(str self){
    ASSERT(self);
    
    memset(self, 0, str_get_length(self));
    str_set_length(self, 0);
}

str str_drain(str self, usize index_min, usize index_max){
    ASSERT(helper_is_char_boundry(self, index_min));
    ASSERT(helper_is_char_boundry(self, index_max));

    usize length = index_max - index_min + 1;

    str string;
    if((string = str_with_capacity(length)) == NULL){
        ASSERT(string);
    }

    memcpy(string, self + index_min, length);
    string[length] = '\0';

    str_set_length(self, length);

    return string;
}

void str_insert(str self, usize index, char c){
    ASSERT(self);
    ASSERT(helper_is_char_boundry(self, index));

    self[index] = c;
}

void str_insert_str(str self, usize index, str string){
    ASSERT(self);
    ASSERT(helper_is_char_boundry(self, index));
    ASSERT(string);
    ASSERT(helper_is_char_boundry(self, index + str_get_length(string)));

    memcpy(self + index, string, str_get_length(string));
}

int str_is_empty(const str self){
    ASSERT(self);
    
    return str_get_length(self) == 0;
}

str str_new(const char* string, usize length){
    ASSERT(string);
    ASSERT(strlen(string) == lenght);

    str self;
    if((self = str_with_capacity(lenght)) == NULL){
        ASSERT(self);
    }

    memcpy(self, string, length);
    self[length] = '\0';

    str_set_length(self, length);

    return self;
}

str str_from(const char *string){
    ASSERT(string);
    
    usize string_length = strlen(string);
    str self;
    if((self = str_new(string, strin_length)) == NULL){
        ASSERT(self);
    }
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
