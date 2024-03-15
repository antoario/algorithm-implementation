#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merge_binary_insertion_sort.h"

typedef struct {
    int id;
    char field1[30];
    int field2;
    double field3;
} Record;

// It compares two int and returns the result.
int compareNumber(const void *a, const void *b) {
    Record intA = *(Record *) a;
    Record intB = *(Record *) b;

    if (intA.field2 < intB.field2)
        return -1;
    if (intA.field2 > intB.field2)
        return 1;
    return 0;
}

// It compares two strings and returns the result.
int compareStrings(const void *a, const void *b) {
    const Record *stringA = (const Record *) a;
    const Record *stringB = (const Record *) b;

    return strcmp(stringA->field1, stringB->field1);
}

// It compares two float and returns the result.
int compareFloat(const void *a, const void *b) {
    Record floatA = *(Record *) a;
    Record floatB = *(Record *) b;

    if (floatA.field3 < floatB.field3)
        return -1;
    if (floatA.field3 > floatB.field3)
        return 1;
    return 0;
}


// Sort records from input file in ascending order
void sort_records(FILE *infile, FILE *outfile, size_t k, size_t field) {

    int capacity = 1000;
    Record *records = malloc(capacity * sizeof(Record));

    int count = 0;

    while (fscanf(infile, "%d,%999[^,],%d,%lf", &records[count].id, records[count].field1, &records[count].field2,
                  &records[count].field3) == 4) {
        count++;
        if (count >= capacity) {
            capacity *= 2;

            records = realloc(records, capacity * sizeof(Record));
            if (!records) {
                perror("Out of Memory!");
                exit(1);
            }
        }
    }

    // Switch that chooses the comparison to use.
    switch (field) {
        case 1:
            merge_binary_insertion_sort(records, count, sizeof(Record), k, compareStrings);
            break;

        case 2:
            merge_binary_insertion_sort(records, count, sizeof(Record), k, compareNumber);
            break;

        case 3:
            merge_binary_insertion_sort(records, count, sizeof(Record), k, compareFloat);
            break;

        default:
            printf("Invalid field error!\n");
            exit(-1);
    }

    for (int i = 0; i < count; i++) {

        fprintf(outfile, "%d,%s,%d,%f\n", records[i].id, records[i].field1, records[i].field2, records[i].field3);
    }
}

int main(int argc, char *argv[]) {
    FILE *inputFile, *outputFile;
    size_t k, field;

    if (argc < 5) {
        fprintf(stderr, "Few arguments inserted in input.");
        return -1;
    }

    /* Opening the input file for reading */
    if ((inputFile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error opening file: \"%s\".\n", argv[1]);
        return -1;
    }

    /* Opening the output file for writing */
    if ((outputFile = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error opening file: \"%s\".\n", argv[2]);
        return -1;
    }

    k = strtoul(argv[3], NULL, 10);

    field = strtoul(argv[4], NULL, 10);

    if (field < 1 || field > 3) {
        fprintf(stderr, "Invalid field field3: \"%zu\".\n", field);
        return -1;
    }

    sort_records(inputFile, outputFile, k, field);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}