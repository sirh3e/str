#include "str.h"
#include "strlib.h"

#include<string.h>

static inline usize str_get_type_size(u8 type){
    switch(type){
        case STR_TYPE_STR8:
            return sizeof(struct str8);
    }
    return 0;
}

str str_with_capacity(usize capacity){
    capacity += 1;

    str string = NULL;
    usize type_size = str_get_type_size(STR_TYPE_STR8); //ToDo change it make it dynamic
    usize size = capacity * sizeof(char) + type_size;

    void* ptr;
    if((ptr = (void*)str_malloc(size)) == NULL){
        //ToDo null handling
    }
    
    memset(ptr, 0, size); 
    string = (char*)ptr+type_size;

    str_set_allocated(string, capacity);

    return string;
}
