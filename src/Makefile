# Author:  Menglong TAN <tanmenglong@gmail.com>
# Date:    Mon Apr 21 16:44:08 2014
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include ../Makefile.env

BUILD_TARGETS = libwuhan.a libwuhan_debug.a

INC = -I../include/ -I./

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ_DEBUG = $(patsubst %.c, %_d.o, $(SRC))

.PHONY : all clean

all : $(BUILD_TARGETS)

libwuhan.a : $(OBJ)
ifeq ($(OS), Darwin)
	libtool -static -o $@ $^
else
	ar -cr -o $@ $^
endif

libwuhan_debug.a : $(OBJ_DEBUG)
ifeq ($(OS), Darwin)
	libtool -static -o $@ $^
else
	ar -cr -o $@ $^
endif

clean :
	rm -rf $(OBJ) $(OBJ_DEBUG) $(BUILD_TARGETS)
