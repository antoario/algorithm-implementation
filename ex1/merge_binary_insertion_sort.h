#ifndef EX1_MERGE_BINARY_INSERTION_SORT_H
#define EX1_MERGE_BINARY_INSERTION_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/**
 * Wrapper function for merge sort.
 *
 * @param base: pointer to first element of array.
 * @param nitems: number of elements in the array.
 * @param size: size in bytes for each element in the array.
 * @param k: parameter.
 * @param compar: criterion by which to order the data.
 */
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *
                                                                                                 , const void *));
/**
 * It sort the array passed as argument using compare parameter.
 *
 * @param arr: array to sort.
 * @param leftIndex: index of the first item of the array.
 * @param rightIndex: index of the last item of the array.
 * @param k: parameter.
 * @param elementSize: size in bytes for each element in the array.
 * @param compare: criterion by which to order the data.
 */
void
merge_sort(void *arr, int leftIndex, int rightIndex, size_t k, size_t elementSize, int (*compare)(const void *, const void *));

/**
 * It executes a binary search to find the position in which to insert each element during sorting.
 *
 * @param base: pointer to first element of array.
 * @param nitems: number of items in the array.
 * @param size: size in bytes for each element in the array.
 * @param compar: criterion by which to order the data.
 */
void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));

/**
 * It finds the correct insertion position.
 *
 * @param base: pointer to first element of array.
 * @param size: size in bytes for each element in the array.
 * @param compar: criterion by which to order the data.
 * @param item: item to research.
 * @param leftIndex: index of the first item of the array.
 * @param rightIndex: index of the last item of the array.
 * @return int value that represents the correct insertion position.
 */
int binary_search(const void *base, size_t size, int (*compar)(const void *, const void *), const void *item, int leftIndex
        , int rightIndex);

/**
 * It merges two subarray of arr. First subarray is arr[left..middle], second subarray is arr[middle+1..right].
 *
 * @param arr: array to merge.
 * @param leftIndex: index of the first item of the array.
 * @param middleIndex: index of the middle item of the array.
 * @param rightIndex: index of the last item of the array.
 * @param elementSize: size in bytes for each element in the array.
 * @param compare: criterion by which to order the data.
 */
void merge(void *arr, int leftIndex, int middleIndex, int rightIndex, size_t elementSize, int (*compare)(const void *, const void *));

#endif
