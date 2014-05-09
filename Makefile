# Author:  Tan Menglong <tanmenglong@gmail.com>
# Date:    Mon Apr 21 00:54:20 2014
#
# Make Target:
# ------------
# The Makefile provides the following targets to make:
#   $ make           compile and link
#   $ make clean     clean objects and the executable file
#
#===========================================================================

include Makefile.env

.PHONY : all src test examples output clean check help

all : output

output : src examples
	mkdir -p output

clean :
	rm -rf output
	make clean -C src
	make clean -C examples
	make clean -C test

src :
	make -C src

examples : all
	make -C examples

test : all
	make -C test
	make test -C test

check : all
	make -C test
	make check -C test

help :
	@echo 'Usage: make [TARGET]'
	@echo 'TARGETS:'
	@echo '  all       (=make) compile and link.'
	@echo '  clean     clean objects and the executable file.'
	@echo '  help      print this message.'
	@echo
