#TODO: Complete the MAkefile to compile rpn
#
#  NOTES:
#  (1) you must use clang as your compiler
#  (2) you must compile to .o object files and combine them into an executable
#  (3) you must have a clean to remove binary and .o files
#  (4) you MAY NOT use Makefile vairables, like CC or CFLAGS
#
#  (hint: don't foget about adding in the readline library via -l)

all: rpn

rpn: rpn.o mathlib.o
	clang rpn.o mathlib.o -l readline -o rpn

mathlib.o: mathlib.c mathlib.h
	clang -c mathlib.c -o mathlib.o

rpn.o: rpn.c 
	clang -c rpn.c -o rpn.o
clean:
	rm -f rpn *.o

# COMPLETE BLEOW

