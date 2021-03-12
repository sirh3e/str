#include <assert.h>
#include <string.h>
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

#define TEST_ASSERT_LENGTH_CMP(str1, str2, length)                          \
    TEST_ASSERT(strncmp(str1, str2, length + 1) == 0);                      \
    TEST_ASSERT(length == str_get_length(str1) && length == str_get_length(str2))

#define TEST_ASSERT_EQ(left, right) \
    TEST_ASSERT_MESSAGE_EQ(#left, left, #right, right) 

#define TEST(string, capacity, length, type)                        \
    TEST_ASSERT(string);                                            \
    TEST_ASSERT_EQ(capacity, str_get_capacity(string));             \
    TEST_ASSERT_EQ(length, str_get_length(string));                 \
    TEST_ASSERT_EQ((type & STR_TYPE_MASK), str_get_flags(string)) 

#define TEST_ASSERT_CMP(str1, str2, length)                                         \
    TEST_ASSERT(str1);                                                              \
    TEST_ASSERT(str2);                                                              \
    TEST(str1, str_get_capacity(str2), str_get_length(str2), str_get_type(str2));   \
    TEST_ASSERT_LENGTH_CMP(str1, str2, length);                                     \
    TEST_ASSERT(str_get_flags(str1) == str_get_flags(str2))
    
void test_str_clear();
void test_str_copy();
//ToDo add test_str_drain();
void test_str_from();

int main(int argc, char** argv){

    test_str_clear();
    test_str_copy();
    //test_str_drain();
    test_str_from();

    return 0;
}

void test_str_clear(){
    char* name = "sirh3e";
    usize capacity = 7;
    usize length = strlen(name);

    str string = str_new(name, length);
    TEST(string, capacity, length, STR_TYPE_STR8);
    assert(strncmp(name, string, length + 1) == 0);

    capacity = 7;
    length = 0;
    str_clear(string);
    TEST(string, capacity, length, STR_TYPE_STR8);

    str_free(string);
}

void test_str_copy(){
    char* name = "sirh3e";
    usize length = strlen(name);
    usize capacity = length + 1;

    str string = str_new(name, length);
    TEST(string, capacity, length, STR_TYPE_STR8);
    assert(strncmp(name, string, length + 1) == 0);

    str string_copy = str_copy(string);
    TEST(string_copy, capacity, length, STR_TYPE_STR8);
    TEST_ASSERT_CMP(string_copy, string, length);

    str_free(string);
    str_free(string_copy);
}

void test_str_from(){
    char* name = "sirh3e";
    usize length = strlen(name);
    usize capacity = length + 1;

    str string = str_from(name);
    TEST(string, capacity, length, STR_TYPE_STR8);
    assert(strncmp(name, string, length + 1) == 0);

    str_free(string);
}
