#include "../ex1/unit_testing/unity.h"
#include "skiplist.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}


int compare_strings(const void *a, const void *b) {
    return strcmp(a, b);
}

void test_new_skiplist(void) {
    struct SkipList* list = NULL;
    new_skiplist(&list, 5, compare_strings);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(5, list->max_height);
    clear_skiplist(&list);
}

void test_insert_skiplist(void) {
    struct SkipList* list = NULL;
    new_skiplist(&list, 5, compare_strings);
    char* item = "test";
    insert_skiplist(list, strdup(item));
    const void* result = search_skiplist(list, "test");
    TEST_ASSERT_EQUAL_STRING("test", result);
    clear_skiplist(&list);
}

void test_search_skiplist(void) {
    struct SkipList* list = NULL;
    new_skiplist(&list, 5, compare_strings);
    char* item = "test";
    insert_skiplist(list, strdup(item));
    const void* result = search_skiplist(list, item);
    TEST_ASSERT_EQUAL_STRING("test", result);
    result = search_skiplist(list, "nonexistent");
    TEST_ASSERT_NULL(result);
    clear_skiplist(&list);
}

void test_clear_skiplist(void) {
    struct SkipList* list = NULL;
    new_skiplist(&list, 5, compare_strings);
    char* item = "test";
    insert_skiplist(list, strdup(item));
    clear_skiplist(&list);
    TEST_ASSERT_NULL(list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_skiplist);
    RUN_TEST(test_insert_skiplist);
    RUN_TEST(test_search_skiplist);
    RUN_TEST(test_clear_skiplist);
    return UNITY_END();
}