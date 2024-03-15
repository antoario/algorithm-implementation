#include "skiplist.h"

static struct Node* create_node(void *item, size_t level) {
    struct Node *node = malloc(sizeof(struct Node));
    node->next = calloc(level, sizeof(struct Node*));
    node->size = level;
    node->item = item;

    return node;
} // create_node


static size_t random_level(size_t max_height) {
    size_t lvl = 1;
    while (rand() < (RAND_MAX / 2) && lvl < max_height) {
        lvl++;
    } // while

    return lvl;
} // random_level


void new_skiplist(struct SkipList **list, size_t max_height, int (*compar)(const void*, const void*)) {
    srand(time(NULL));
    *list = malloc(sizeof(struct SkipList));

    (*list)->heads = calloc(max_height, sizeof(struct Node*));
    (*list)->max_level = 1;
    (*list)->max_height = max_height;
    (*list)->compare = compar;
} // new_skiplist


void clear_skiplist(struct SkipList **list) {
    struct Node* node;
    struct Node* next_node;
    node = (*list)->heads[0];

    while (node != NULL) {
        // save the next and free the current node
        next_node = node->next[0];
        free(node->item);
        free(node->next);
        free(node);

        node = next_node;
    } // while

    free((*list)->heads);
    free(*list);
    *list = NULL;
} // clear_skiplist


void insert_skiplist(struct SkipList *list, void *item) {
    size_t new_level = random_level(list->max_height);
    struct Node *new_node = create_node(item, new_level);

    if (new_node->size > list->max_level) {
        list->max_level = new_node->size;
    }

    struct Node **x = list->heads;
    for (ssize_t k = list->max_level - 1; k >= 0; --k) {
        while (x[k] != NULL && list->compare(x[k]->item, item) < 0) {
            x = x[k]->next;
        } // while

        if (k < new_node->size) {
            new_node->next[k] = x[k];
            x[k] = new_node;
        }
    } // for
} // insert_skiplist


const void* search_skiplist(struct SkipList *list, void *item) {
    struct Node **x = list->heads;

    for (ssize_t i = list->max_level - 1; i >= 0; --i) {
        while (x[i] != NULL && list->compare(x[i]->item, item) < 0) {
            x = x[i]->next;
        } // while
    } // for

    if (x[0] != NULL && list->compare(x[0]->item, item) == 0) {
        return x[0]->item;
    }

    return NULL;
} // search_skiplist
