CC=gcc
CFLAGS= -Wall -Werror -Wextra -std=c11 
TST_CFLAGS:= -g $(CFLAGS) $(FS)
LDFLAGS=-lcheck -lpthread -lm -I /usr/local/include -L/usr/local/lib
CHECK:=$(shell pkg-config --cflags --libs check)
FS=-fsanitize=address -g
LINUX_FLAGS=-lsubunit -lrt -lpthread -lm
VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)  
	OPEN_CMD = xdg-open
	ADD_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURCE 
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open
	ADD_LIB = 
endif

SRC=$(wildcard s21_*.c)
OBJ=$(patsubst %.c,%.o, ${SRC})
TARGET=test
FILE_TEST=$(wildcard ./unit_test/*.c)

all: clean s21_matrix.a test


s21_matrix.a:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(SRC)
	ar -rcs $@ $(OBJ)


test: clean s21_matrix.a
	$(CC) -g $(CFLAGS) $(LDFLAGS) --coverage $(FILE_TEST) s21_matrix.a -o $@ $(CHECK) $(ADD_LIB) -lcheck
	./$(TARGET)


gcov_report: test
	$(CC) --coverage $(CFLAGS) $(LDFLAGS) $(FILE_TEST) s21_matrix.a $(SRC) -o test $(CHECK) -lm 
	./test
	lcov -t "test" -o tests.info -c -d .
	genhtml -o coverage tests.info
	open coverage/index.html


clean:
	rm -f *.a *.o *.gcda *.gcno *.info *.out test
	rm -rf coverage test.dSYM

valgrind: rebuild
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test 

rebuild: all


rebuild_gcov: clean test gcov_report s21_matrix_gcov.a

leaks: rebuild
	leaks -atExit -- ./test

clang:
	clang-format -style=Google -n *.c *.h
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -n */*.c
	clang-format -style=Google -i */*.c