#include "skiplist.h"


char* normalize_word(const char* word) {
    int length = strlen(word);
    char* normalized = malloc(length + 1);

    int j = 0;
    for (int i = 0; i < length; i++) {
        if (isalpha(word[i])) {
            normalized[j] = tolower(word[i]);
            j++;
        }
    }
    normalized[j] = '\0';

    return normalized;
}

int string_compare(const void *a, const void *b) {
    return strcmp((const char*)a, (const char*)b);
}

void find_errors(FILE *dictfile, FILE *textfile, size_t max_height) {
    struct SkipList *list = NULL;
    new_skiplist(&list, max_height, string_compare);

    char word[256];
    while (fscanf(dictfile, "%255s", word) == 1) {
        insert_skiplist(list, strdup(word));
    }

    while (fscanf(textfile, "%255s", word) == 1) {
        char* normalized = normalize_word(word);
        if (search_skiplist(list, normalized) == NULL) {
            printf("%s\n", normalized);
        }
    }

    clear_skiplist(&list);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s dictfile textfile max_height.\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dictfile_path = argv[1];
    const char *textfile_path = argv[2];
    size_t max_height = atoi(argv[3]);

    FILE *dictfile = fopen(dictfile_path, "r");
    if (dictfile == NULL) {
        perror("Could not open dictfile.");
        return EXIT_FAILURE;
    }

    FILE *textfile = fopen(textfile_path, "r");
    if (textfile == NULL) {
        perror("Could not open textfile.");
        fclose(dictfile);
        return EXIT_FAILURE;
    }

    find_errors(dictfile, textfile, max_height);

    fclose(textfile);
    fclose(dictfile);

    return EXIT_SUCCESS;
}