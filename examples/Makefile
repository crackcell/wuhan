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

TEST_SRC = $(wildcard *_example.c)
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_SRC))
BUILD_TARGETS = $(patsubst %.c, %, $(TEST_SRC))

.PHONY : all clean

all : $(BUILD_TARGETS)

example :
	for file in $(wildcard *_example); \
		do ./$$file; \
	done;

clean :
	rm -rf $(TEST_OBJ) $(BUILD_TARGETS)

%_example : %_example.o
	$(CC) -o $@ $^ $(OBJ) $(LIB)
