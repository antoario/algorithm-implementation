OUT = ./bin

$(shell mkdir -p $(OUT))

all: main_ex2.c skiplist.c
	gcc -g -o $(OUT)/main_ex2 main_ex2.c skiplist.c

test: test_skiplist.c ../ex1/unit_testing/unity.c
	gcc -g -o $(OUT)/test_skiplist test_skiplist.c ../ex1/unit_testing/unity.c skiplist.c