# TODO 
all: runme dontrunme

runme: runme.o  library.o
	clang runme.o library.o -o runme

dontrunme: dontrunme.o fun.o library.o
	clang dontrunme.o library.o fun.o -o dontrunme

runme.o: runme.c
	clang -c runme.c -o runme.o

library.o: library.c library.h
	clang -c library.c -o library.o

dontrunme.o: dontrunme.c
	clang -c dontrunme.c -o dontrunme.o

fun.o: fun.c fun.h
	clang -c fun.c -o fun.o

clean:
	rm -f runme dontrunme