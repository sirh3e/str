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

str str_from(const char *string){
    ASSERT(string);
    
    str self;
    usize string_length = strlen(string);
    if((self = str_new(string, string_length)) == NULL){
        ASSERT(self);
    }
    return self;
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
    ASSERT(strlen(string) == length);

    str self;
    if((self = str_with_capacity(length)) == NULL){
        ASSERT(self);
    }

    memcpy(self, string, length);
    self[length] = '\0';

    str_set_length(self, length);

    return self;
}

char str_pop(str self){
    ASSERT(self);
    
    usize length_old = str_get_length(self);
    usize length_new = length_old == 0 ? 0 : length_old - 1;
    
    char c = self[length_old];

    self[length_new] = '\0';
    str_set_length(self, length_new);

    return c;
}

void str_push(str self, char c){
    ASSERT(self);
    //ToDo check for allocated size

    usize length = str_get_length(self);
    
    self[length++] = c;
    self[length] = '\0';

    str_set_length(self, length);
}

void str_push_str(str self, str string){
    ASSERT(self);
    ASSERT(string);
    //ToDo check for allocated size

    usize self_length = str_get_length(self);
    usize string_length = str_get_length(string);
    usize length = self_lenght + string_length;

    memcpy(self + self_length, string, string_length);
    self[length] = '\0';

    str_set_length(self, length);
}

char str_remove(str self, usize index){
    ASSERT(self);

    char c = '\0';
    usize length = str_get_length(self);

    if(index >= length){
        return c;
    }

    c = self[index];

    memcpy(self + index, self + index + 1, length - index);

    return c;
}

void str_shrink_to(str self, usize capacity){
    ASSERT(self);
    ASSERT(str_get_capacity(self) < capacity);

    if(str_get_capacity(self) == capacity){
        return;
    }
    
    u8 type = str_get_type(self);
    usize struct_size = str_get_struct_size(type);
    usize length = str_get_length(self);
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
