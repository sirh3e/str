#include <stdio.h>
#include "str.h"

int main(int argc, char** argv){

    str string;
    if((string = str_with_capacity(127)) == NULL){
        exit(1);
    }

    printf("%s allocated: %zu length: %zu\n", string, str_get_allocated(string), str_get_length(string));
    printf("%d\n", str_get_flags(string));

    str_set_flags(string, 169);
    printf("%d\n", str_get_flags(string));

    return 0;
}
