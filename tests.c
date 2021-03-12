#include <assert.h>
#include <stdio.h>
#include "str.h"

#define STR_TEST_COLOR_REST     "\033[0m"
#define STR_TEST_COLOR_RED      "\033[31m"
#define STR_TEST_COLOR_GREEN    "\033[32m"

#define TEST_ASSERT_MESSAGE_EQ(left_string, left_value, right_string, right_value)                                  \
            printf("[ %s%s%s ] file: [%s] function: [%s] line: [%d] expression: [%s %s %s] values: [%lu %s %lu]\n", \
                left_value == right_value ? STR_TEST_COLOR_GREEN : STR_TEST_COLOR_RED,                              \
                left_value == right_value ? "PASSED" : "FAILED", STR_TEST_COLOR_REST,                               \
                __FILE__, __func__, __LINE__,                                                                       \
                #left_string, "==", #right_string,                                                                  \
                left_value, "==", right_value                                                                       \
            )

#define TEST_ASSERT(expression) \
    assert(expression)
                
#define TEST_ASSERT_EQ(left, right) \
    TEST_ASSERT_MESSAGE_EQ(#left, left, #right, right) 

#define TEST(string, capacity, length, type)                        \
    TEST_ASSERT(string);                                            \
    TEST_ASSERT_EQ(capacity, str_get_capacity(string));             \
    TEST_ASSERT_EQ(length, str_get_length(string));                 \
    TEST_ASSERT_EQ((type & STR_TYPE_MASK), str_get_flags(string)) 

int main(int argc, char** argv){

    usize capacity = 127;
    usize length = 0;
    
    str string = str_with_capacity(capacity); 
    TEST(string, capacity, length, STR_TYPE_STR8);
    
    str_clear(string);
    TEST(string, capacity, length, STR_TYPE_STR8);

    capacity = 4;
    length = capacity;
    string = str_new("sirh3e", length);
    TEST(string, capacity, length, STR_TYPE_STR8);
    
    return 0;
}
