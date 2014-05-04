# Author:  Tan Menglong <tanmenglong@gmail.com>
# Date:    Tue Apr 22 11:32:55 2014
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include ../Makefile.env

INC = -I../include -I../src
LIB = -lpthread
ifeq ($(OS), Linux)
	LIB += -lm
endif

OBJ = ../src/libwuhan.a

TEST_SRC = $(wildcard *_test.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
BUILD_TARGETS = $(patsubst %.c, %, $(TEST_SRC))

.PHONY : all clean src check

all : $(BUILD_TARGETS)

test :
	for file in $(wildcard *_test); \
		do ./$$file; \
	done;

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_test : %_test.o
	$(CC) -o $@ $^ $(OBJ) $(LIB)

check : $(BUILD_TARGETS)
	for file in $(wildcard *_test); \
		do valgrind --leak-check=full ./$$file; \
	done;
