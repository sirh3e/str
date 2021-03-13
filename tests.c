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
void test_str_insert();
void test_str_insert_str();
void test_str_is_empty();
void test_str_new();

int main(int argc, char** argv){

    test_str_clear();
    test_str_copy();
    //test_str_drain();
    test_str_from();
    test_str_insert();
    test_str_insert_str();
    test_str_is_empty();
    test_str_new();
    
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

void test_str_insert(){
    char* text = "abcdef";
    str text_string = str_from(text);
    usize text_index = 0;
    usize text_length = str_get_length(text_string);
    usize capacity = strlen(text) + 1;
    
    str string = str_from("zzzzzz");
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    //a
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);
    text_index += 1;
    
    //b
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);
    text_index += 1;

    //c
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);
    text_index += 1;
    
    //d
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);
    text_index += 1;
    
    //e
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);
    text_index += 1;
    
    //f
    str_insert(string, text_index, text[text_index]);
    TEST(string, capacity, text_length, STR_TYPE_STR8);
    TEST_ASSERT(strncmp(string, text_string, text_index) == 0);

    str_free(text_string);
    str_free(string);
}

void test_str_insert_str(){
    char* text1 = "abc";
    usize text1_capacity = strlen(text1) + 1;
    usize text1_length = text1_capacity - 1;
   
    str str1 = str_from(text1);
    TEST(str1, text1_capacity, text1_length, STR_TYPE_STR8);
    assert(strncmp(str1, text1, text1_capacity) == 0);

    char* text2 = "def";
    usize text2_capacity = strlen(text2) + 1;
    usize text2_length = text2_capacity - 1;
   
    str str2 = str_from(text2);
    TEST(str2, text2_capacity, text2_length, STR_TYPE_STR8);
    assert(strncmp(str2, text2, text2_capacity) == 0);

    usize text3_capacity = text1_length + text2_length + 1;
    usize text3_length = text3_capacity - 1;

    str str3 = str_from("zzzzzz");
    TEST(str3, text3_capacity, text3_length, STR_TYPE_STR8);

    str_insert_str(str3, 0, str2);
    TEST_ASSERT(strncmp(str3, "defzzz", text3_capacity) == 0);
    
    str_insert_str(str3, 3, str1); 
    TEST_ASSERT(strncmp(str3, "defabc", text3_capacity) == 0);
}

void test_str_is_empty(){
    str string = NULL;

    string = str_with_capacity(16);
    TEST_ASSERT(string);
    TEST_ASSERT_EQ(str_is_empty(string), 1);
    str_free(string);
   
    string = str_from("sirh3e");
    TEST_ASSERT(string);
    TEST_ASSERT_EQ(str_is_empty(string), 0);
    str_free(string);
}

void test_str_new(){
    char* text = "sirh3e";
    usize text_length = strlen(text);
    str string = str_new(text, text_length);
    TEST_ASSERT(string);
    TEST_ASSERT_EQ(str_is_empty(string), 0);
    TEST_ASSERT_EQ(str_get_capacity(string), text_length + 1);
    TEST_ASSERT_EQ(str_get_length(string), text_length);
    TEST_ASSERT_EQ(str_get_flags(string), (STR_TYPE_STR8 & STR_TYPE_MASK));
    TEST_ASSERT_EQ(strncmp(string, text, text_length + 1), 0);
    str_free(string);

    text = "sir";
    text_length = strlen(text);
    string = str_new(string, text_length);
    TEST_ASSERT(string);
    TEST_ASSERT_EQ(str_is_empty(string), 0);
    TEST_ASSERT_EQ(str_get_capacity(string), text_length + 1);
    TEST_ASSERT_EQ(str_get_length(string), text_length);
    TEST_ASSERT_EQ(str_get_flags(string), (STR_TYPE_STR8 & STR_TYPE_MASK));
    TEST_ASSERT_EQ(strncmp(string, text, text_length + 1), 0);
    str_free(string);
    
    text = "abcdefghijklmnopqrstuvwxyz";
    text_length = strlen(text);
    string = str_new(text, text_length);
    TEST_ASSERT(string);
    TEST_ASSERT_EQ(str_is_empty(string), 0);
    TEST_ASSERT_EQ(str_get_capacity(string), text_length + 1);
    TEST_ASSERT_EQ(str_get_length(string), text_length);
    TEST_ASSERT_EQ(str_get_flags(string), (STR_TYPE_STR8 & STR_TYPE_MASK));
    TEST_ASSERT_EQ(strncmp(string, text, text_length + 1), 0);
    str_free(string);
}
