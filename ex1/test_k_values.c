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
float sort_records(Record * records, int count, int field, FILE * outfile, int k) {


    float startTime = (float) clock() / CLOCKS_PER_SEC;

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

    float endTime = (float) clock() / CLOCKS_PER_SEC;

    return endTime - startTime;

}

int main(int argc, char *argv[]) {
    FILE *inputFile, *outputFile, *benchmark;
    size_t k, field;
    int capacity = 1000, count = 0;
    Record *records = malloc(capacity * sizeof(Record));

    if (argc < 4) {
        fprintf(stderr, "Few arguments inserted in input.");
        return -1;
    }

    if ((benchmark = fopen("benchmark.csv", "w")) == NULL) {
        fprintf(stderr, "Error opening file: \"%s\".\n", argv[1]);
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

    field = strtoul(argv[3], NULL, 10);
    fprintf(benchmark, "k val, time\n");

    while (fscanf(inputFile, "%d,%999[^,],%d,%lf", &records[count].id, records[count].field1, &records[count].field2,
                  &records[count].field3) == 4) {
        count++;
        if (count >= capacity) {
            capacity += 10000;

            records = realloc(records, capacity * sizeof(Record));
            if (!records) {
                perror("Out of Memory!");
                exit(1);
            }
        }
    }

    for (int i = 10; i < 51; i+=5) {
        Record *recordDis = malloc(count * sizeof(Record));
        if (!recordDis) {
            perror("Out of Memory!");
            exit(1);
        }
        memcpy(recordDis, records, count * sizeof(Record));
        float val = sort_records(recordDis, count, field, outputFile, i);

        fprintf(benchmark, "%d, %.6f\n", i, val);
        free(recordDis);
    }

    fclose(benchmark);
    fclose(inputFile);
    fclose(outputFile);
}