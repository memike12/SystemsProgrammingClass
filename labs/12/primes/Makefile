CC=clang
CFLAGS=-g -Wall -lpthread -lm
SRC=$(wildcard *.c)
BIN=$(SRC:.c=)

all:$(BIN)

clean: 
	rm -rf $(BIN) *~
	rm -rf *.dSYM