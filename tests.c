#include <stdio.h>
#include "str.h"

#define STR_TEST_COLOR_REST "\033[0m"
#define STR_TEST_COLOR_RED "\033[31m"
#define STR_TEST_COLOR_GREEN "\033[32m"

#define TEST_ASSERT_MESSAGE(expression, message) \
            printf("[ %s%s%s ] file: [%s] function: [%s] line: [%d] [%s]\n", \
            expression ? STR_TEST_COLOR_GREEN : STR_TEST_COLOR_RED, expression ? "PASSED" : "FAILED", STR_TEST_COLOR_REST, \
            __FILE__, __func__, __LINE__, message)

#define TEST_ASSERT(expression) \
           TEST_ASSERT_MESSAGE(expression, #expression)

int main(int argc, char** argv){

    usize capacity = 127;
    str string;
    if((string = str_with_capacity(capacity)) == NULL){
        exit(1);
    }
    TEST_ASSERT(string != NULL);
    TEST_ASSERT(str_get_capacity(string) == capacity + 1);
    TEST_ASSERT(str_get_length(string) == 0);
    TEST_ASSERT(str_get_flags(string) == (STR_TYPE_STR8 & STR_TYPE_MASK));

    str_clear(string);
    TEST_ASSERT(str_get_capacity(string) == capacity + 1);
    TEST_ASSERT(str_get_length(string) == 0);
    TEST_ASSERT(str_get_flags(string) == (STR_TYPE_STR8 & STR_TYPE_MASK));

    return 0;
}
