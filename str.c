#include <assert.h>
#include <string.h>

#include "str.h"
#include "strlib.h"

#define ASSERT(expression) \
    assert(expression)

void* helper_get_origin_ptr(str self);
usize helper_get_struct_size(str self);
usize helper_get_struct_size_from_type(u8 type);
u8 helper_get_type_from_capacity(usize capacity);
int helper_is_char_boundry(str self, usize index);

void* helper_get_origin_ptr(str self){
    ASSERT(self);

    usize struct_size = helper_get_struct_size(self);
    return self - struct_size;
}

usize helper_get_struct_size(str self){
    ASSERT(self);

    u8 type = str_get_type(self);
    return str_get_struct_size(type);
}

usize helper_get_struct_size_from_type(u8 type){
    switch(type & STR_TYPE_MASK){
        case STR_TYPE_STR8:
            return sizeof(struct str8);
    }
    return 0;
}

u8 helper_get_type_from_capacity(usize capacity){
    //ToDo check for other types, capacity boundries
    return STR_TYPE_STR8 & STR_TYPE_MASK;
}

int helper_is_char_boundry(str self, usize index){
    ASSERT(self);

    return index < str_get_capacity(self) && index <= str_get_length(self);
}

void str_clear(str self){
    ASSERT(self);
    
    memset(self, 0, str_get_length(self));
    str_set_length(self, 0);
}

str str_copy(str self){
    ASSERT(self);

    void* origin_ptr = helper_get_origin_ptr(self);
    u8 flags = str_get_flags(self);
    u8 type = str_get_type(self);
    usize capacity = str_get_capacity(self);
    usize length = str_get_length(self);

    usize struct_size = str_get_struct_size(type);

    void* ptr;
    if((ptr = malloc(struct_size + capacity)) == NULL){
        return ptr;
    }

    str string = NULL;
    memcpy(ptr, origin_ptr, struct_size + capacity);
    
    string = (str)ptr + struct_size;
    string[length] = '\0';

    str_set_flags(string, flags);
    str_set_capacity(string, capacity);
    str_set_length(string, length);

    return string;
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
    ASSERT(length <= strlen(string));

    str self;
    if((self = str_with_capacity(length + 1)) == NULL){
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
    
    char c = self[length_new];
    self[length_new] = '\0';
    
    str_set_length(self, length_new);

    return c;
}

void str_push(str self, char c){
    ASSERT(self);
    //ToDo check for allocated size

    usize length = str_get_length(self);
    
    self[length] = c;
    self[++length] = '\0';

    str_set_length(self, length);
}

void str_push_str(str self, str string){
    ASSERT(self);
    ASSERT(string);
    //ToDo check for allocated size

    usize self_length = str_get_length(self);
    usize string_length = str_get_length(string);
    usize length = self_length + string_length;

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

    usize current_capacity = str_get_capacity(self);
    usize current_length = str_get_length(self);
    usize current_struct_size = helper_get_struct_size(self);

    usize shrink_length = current_capacity - capacity;

    if(shrink_length == 0){
        return;
    }
    
    u8 new_type = helper_get_type_from_capacity(capacity);
    usize new_struct_size = helper_get_struct_size_from_type(new_type);
    usize new_length = current_length < capacity ? current_length : capacity;

    usize delta_struct_size = current_struct_size - new_struct_size;

    memcpy(self - delta_struct_size, self, new_length);
    void* current_origin_ptr = helper_get_origin_ptr(self);

    if((self = strlib_realloc(current_origin_ptr, new_struct_size + capacity)) == NULL){
        ASSERT(self);
    }
    self[new_length] = '\0';

    str_set_type(self, new_type);
    str_set_capacity(self, capacity);
    str_set_length(self, new_length);
}

void str_shrink_to_fit(str self){
    ASSERT(self);

    str_shrink_to(self, str_get_length(self));
}

str str_split_off(str self, usize at){
    ASSERT(self);
    ASSERT(helper_is_char_boundry(self, at));

    str other = str_from(self + at);
    if(other == NULL){
        return NULL;
    }

    usize length = at + 1;
    str_set_length(self, length);
    self[length] = '\0';

    return other;
}

void str_truncate(str self, usize length){
    ASSERT(self);
    ASSERT(helper_is_char_boundry(self, length - 1));

    usize current_length = str_get_length(self);

    memset(self, 0, current_length - length);
    self[length] = '\0';

    str_set_length(self, length);
}

str str_with_capacity(usize capacity){
    
    str self;
    capacity = capacity == 0 ? 1 : capacity;
    u8 struct_type = STR_TYPE_STR8;
    usize struct_size = str_get_struct_size(struct_type);
    usize string_size = sizeof(char) * capacity;
    usize malloc_size = struct_size + string_size;

    void *ptr;
    if((ptr = strlib_malloc(malloc_size)) == NULL){
        exit(1); //ToDo find a better way
    }

    memset(ptr, 0, malloc_size);
    self = (str)ptr+struct_size;

    str_set_type(self, struct_type);
    str_set_capacity(self, string_size);
    str_set_length(self, 0);

    return self;
}

void str_free(str string){
    if(string){
        return;
    }

    void* ptr;
    if((ptr = helper_get_origin_ptr(string)) == NULL){
        return;
    }

    strlib_free(ptr);
}
