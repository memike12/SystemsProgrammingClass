CC=clang
CFLAGS=-g -Wall
LDFLAGS=-lreadline
SRC=babypipe.c
BIN=babypipe

all: $(BIN)

0: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

1: $(SRC)
	$(CC) $(CFLAGS) -DPIPE=1 $(SRC) -o $(BIN)

2: $(SRC)
	$(CC) $(CFLAGS) -DPIPE=2 $(SRC) -o $(BIN)

3: $(SRC)
	$(CC) $(CFLAGS) -DPIPE=3 $(SRC) -o $(BIN)


clean:
	rm -f $(BIN) $(OBJ) *~
	rm -rf *.dSYM
