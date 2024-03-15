#include <string.h>
#include "unit_testing/unity.h"
#include "merge_binary_insertion_sort.h"


int compareInt(const void *a, const void *b) {
    int intA = *(int *) a;
    int intB = *(int *) b;

    if (intA < intB)
        return -1;
    if (intA > intB)
        return 1;
    return 0;
}

int compareStrings(const void *a, const void *b) {
    const char *stringA = *(const char **) a;
    const char *stringB = *(const char **) b;
    return strcmp(stringA, stringB);
}

void test_merge_sort_int() {
    int arrayToSort[] = {7, 5, 3, 2, 4, 6, 1};
    int sortedArray[] = {1, 2, 3, 4, 5, 6, 7};
    int length = 7;

    merge_binary_insertion_sort(arrayToSort, length, sizeof(int), 0, compareInt);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(int), length);
}

void test_merge_sort_string() {
    char *arrayToSort[] = {"zucca", "banana", "piccolo", "abaco", "a"};
    char *sortedArray[] = {"a", "abaco", "banana", "piccolo", "zucca"};
    int length = 5;

    merge_binary_insertion_sort(arrayToSort, length, sizeof(char *), 0, compareStrings);

    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(char *), length);
}

void test_binary_insertion_sort_int() {
    int arrayToSort[] = {7, 5, 3, 2, 4, 7, 1};
    int sortedArray[] = {1, 2, 3, 4, 5, 7, 7};
    int length = 7;

    binary_insertion_sort(arrayToSort, length, sizeof(int), compareInt);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(int), length);
}

void test_binary_insertion_sort_string() {
    char *arrayToSort[] = {"zucca", "banana", "piccolo", "abaco", "a"};
    char *sortedArray[] = {"a", "abaco", "banana", "piccolo", "zucca"};
    int length = 5;

    binary_insertion_sort(arrayToSort, length, sizeof(char *), compareStrings);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(char *), length);
}

void test_merge_binary_insertion_sort_int() {
    int arrayToSort[] = {7, 5, 3, 2, 4, 7, 1};
    int sortedArray[] = {1, 2, 3, 4, 5, 7, 7};
    int length = 7;

    merge_binary_insertion_sort(arrayToSort, length, sizeof(int), 3, compareInt);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(int), length);
}


void test_merge_binary_insertion_sort_string() {
    char *arrayToSort[] = {"zucca", "banana", "piccolo", "abaco", "a"};
    char *sortedArray[] = {"a", "abaco", "banana", "piccolo", "zucca"};
    int length = 5;

    merge_binary_insertion_sort(arrayToSort, length, sizeof(char *), 3, compareStrings);
    TEST_ASSERT_EQUAL_MEMORY_ARRAY(sortedArray, arrayToSort, sizeof(char *), length);
}



void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_merge_sort_int);
    RUN_TEST(test_merge_sort_string);
    RUN_TEST(test_binary_insertion_sort_int);
    RUN_TEST(test_binary_insertion_sort_string);
    RUN_TEST(test_merge_binary_insertion_sort_int);
    RUN_TEST(test_merge_binary_insertion_sort_string);

    return UNITY_END();
}