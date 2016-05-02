#TODO: Complete the Makefile for mini-sh, you can follow the token-sh guidlines

all: token-sh mini-sh


token-sh: token-sh.c 
	clang -g -Wall -lreadline token-sh.c -o token-sh

mini-sh: mini-sh.c
	clang -g -Wall -lreadline mini-sh.c -o mini-sh

clean:
	rm token-sh
	rm mini-sh
	rm *~
