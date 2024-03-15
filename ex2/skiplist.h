#ifndef EX2_SKIPLIST_H
#define EX2_SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stddef.h>
#include <ctype.h>

struct SkipList {
    struct Node **heads;
    size_t max_level;
    size_t max_height;
    int (*compare)(const void*, const void*);
};

struct Node {
    struct Node **next;
    size_t size;
    void *item;
};

/**
 * It creates and returns a new node in the skiplist.
 *
 * @param item: pointer to the item to add.
 * @param level: size value.
 * @return new node just created.
 */
static struct Node* create_node(void *item, size_t level);

/**
 *  It generates and returns a random level for node.
 *
 * @param max_height: max number pointers.
 * @return level just generated.
 */
static size_t random_level(size_t max_height);

/**
 * It initializes a new skiplist.
 *
 * @param list: pointer to a pointer to skipList, which will be initialized with the new SkipList.
 * @param max_height: max number pointers.
 * @param compar: criterion by which to order the elements in the skiplist.
 */
void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void*, const void*));

/**
 * It frees the memory used by skiplist.
 *
 * @param list: pointer to a pointer to skipList, which will be cleaned.
 */
void clear_skiplist(struct SkipList **list);

/**
 * It inserts an item into the skiplist.
 *
 * @param list: pointer to the list where the item is to be added.
 * @param item: pointer to the item to add.
 */
void insert_skiplist(struct SkipList *list, void *item);

/**
 * It searches an item inside the skiplist.
 *
 * @param list: pointer to the skiplist in which to search for the item.
 * @param item: pointer to the item to search.
 * @return item if it is there or NULL if not found.
 */
const void* search_skiplist(struct SkipList *list, void *item);

#endif