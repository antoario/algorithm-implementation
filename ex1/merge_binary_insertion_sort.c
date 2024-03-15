#include "merge_binary_insertion_sort.h"


void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t k, int (*compar)(const void *, const void *)) {
    merge_sort(base, 0, nitems - 1, k, size, compar);
} // merge_binary_insertion_sort


void merge_sort(void *arr, int leftIndex, int rightIndex, size_t k, size_t elementSize, int (*compar)(const void *, const void *)) {

    // If the dimension of the array is less than k, use binary insertion sort
    if((rightIndex - leftIndex + 1 < k) && (k != 0)) {
        binary_insertion_sort((char *) arr + leftIndex * elementSize, rightIndex - leftIndex + 1, elementSize, compar);

    } else if(leftIndex < rightIndex) {

            // Same as (left+right)/2, but avoids overflow for large left and right
            int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

            // Sort first and second halves
            merge_sort(arr, leftIndex, middleIndex, k, elementSize, compar);
            merge_sort(arr, middleIndex + 1, rightIndex, k, elementSize, compar);

            merge(arr, leftIndex, middleIndex, rightIndex, elementSize, compar);
    }
} // merge_sort


void binary_insertion_sort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *)) {
    for(size_t i = 1; i < nitems; i++) {
        char temp[size];
        memcpy(temp, (char *) base + i * size, size);

        int j = (int) i - 1;

        // Find the insertion position using binary search
        int position = binary_search(base, size, compar, temp, 0, j);

        // Shift elements to make room for the element to be inserted
        memmove((char *) base + (position + 1) * size, (char *) base + position * size, (j - position + 1) * size);

        // Insert the element at the found position
        memcpy((char *) base + position * size, temp, size);
    }
} // binary_insertion_sort


// Binary Search function to find the correct insertion position
int binary_search(const void *base, size_t size, int (*compar)(const void *, const void *), const void *item, int leftIndex
        , int rightIndex) {
    while(leftIndex <= rightIndex) {

        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;
        const void *mid_ptr = (char *) base + middleIndex * size;
        int compare_result = compar(mid_ptr, item);

        if(compare_result == 0) {
            return middleIndex;
        } else if(compare_result < 0) {
            leftIndex = middleIndex + 1;
        } else {
            rightIndex = middleIndex - 1;
        }
    } // while

    return leftIndex;
} // binary_search


void merge(void *arr, int leftIndex, int middleIndex, int rightIndex, size_t elementSize, int (*compar)(const void *, const void *)) {
    int leftArraySize = middleIndex - leftIndex + 1;
    int rightArraySize = rightIndex - middleIndex;

    // Create temporary array for left and right subarray
    void *leftArray = malloc(leftArraySize * elementSize);
    void *rightArray = malloc(rightArraySize * elementSize);

    // Copy data to temporary arrays leftArray[] and rightArray[]
    memcpy(leftArray, (char *) arr + leftIndex * elementSize, leftArraySize * elementSize);
    memcpy(rightArray, (char *) arr + (middleIndex + 1) * elementSize, rightArraySize * elementSize);

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = leftIndex;
    while(i < leftArraySize && j < rightArraySize) {
        if (compar((char *) leftArray + i * elementSize, (char *) rightArray + j * elementSize) <= 0) {
            memcpy((char *) arr + k * elementSize, (char *) leftArray + i * elementSize, elementSize);
            i++;
        } else {
            memcpy((char *) arr + k * elementSize, (char *) rightArray + j * elementSize, elementSize);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[] and rightArray[], if there are any
    while (i < leftArraySize) {
        memcpy((char *) arr + k * elementSize, (char *) leftArray + i * elementSize, elementSize);
        i++;
        k++;
    }
    while (j < rightArraySize) {
        memcpy((char *) arr + k * elementSize, (char *) rightArray + j * elementSize, elementSize);
        j++;
        k++;
    }

    // Free the memory allocated for the temporary array
    free(leftArray);
    free(rightArray);
} // merge