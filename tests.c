#include <stdio.h>
#include "str.h"

#define STR_TEST_COLOR_REST     "\033[0m"
#define STR_TEST_COLOR_RED      "\033[31m"
#define STR_TEST_COLOR_GREEN    "\033[32m"

#define TEST_ASSERT_MESSAGE(left, right, message)                                                                     \
            printf("[ %s%s%s ] file: [%s] function: [%s] line: [%d] expression: [%ld %s %ld] values: [%ld %s %ld] message: [%s]\n", \
                left == right ? STR_TEST_COLOR_GREEN : STR_TEST_COLOR_RED,                                                \
                left == right ? "PASSED" : "FAILED", STR_TEST_COLOR_REST,                                                 \
                __FILE__, __func__, __LINE__,                                                                                   \
                #left, "==", #right,                                                                                       \
                left, "==", right,                                                                                          \
                message                                                                                                         \
            )

#define TEST_ASSERT_EQ(left, right) \
    TEST_ASSERT_MESSAGE(left, right, "")                   

#define TEST(string, capacity, length, type)                        \
    TEST_ASSERT(string);                                            \
    TEST_ASSERT_EQ(capacity, str_get_capacity(string));             \
    TEST_ASSERT_EQ(length, str_get_length(string));                 \
    TEST_ASSERT_EQ((type & STR_TYPE_MASK), str_get_flags(string)) 

int main(int argc, char** argv){

    usize _capacity = 127;
    usize _length = 0;
    
    //str string = str_with_capacity(_capacity); 
    str string = NULL;
    TEST(string, _capacity, _length, STR_TYPE_STR8);
    /*
    str_clear(string);
    TEST(string, capacity, length, STR_TYPE_STR8);

    capacity = 4;
    length = capacity;
    string = str_new("sirh3e", length);
    TEST(string, capacity, length, STR_TYPE_STR8);
    */
    return 0;
}
