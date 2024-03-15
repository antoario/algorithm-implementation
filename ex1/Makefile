OUT = ./build

$(shell mkdir -p $(OUT))

all: main_ex1.c merge_binary_insertion_sort.c
	gcc -g -o $(OUT)/main_ex1 main_ex1.c merge_binary_insertion_sort.c

test: test_merge_binary_insertion_sort.c unit_testing/unity.c
	gcc -g -o $(OUT)/test_main_ex1 test_merge_binary_insertion_sort.c merge_binary_insertion_sort.c unit_testing/unity.c

benchmark: test_k_values.c merge_binary_insertion_sort.c
	gcc -g -o $(OUT)/benchmark test_k_values.c merge_binary_insertion_sort.c