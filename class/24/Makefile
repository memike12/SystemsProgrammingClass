CC=clang
CFLAGS=-g -Wall -lpthread
SRC=$(wildcard *.c)
BIN=$(SRC:.c=)

all:$(BIN)

clean: 
	rm -rf $(BIN) *~
	rm -rf *.dSYM