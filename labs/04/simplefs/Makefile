
CC=clang
CFLAGS=-Wall -g

BIN=testfs shell

all: $(BIN)

shell: filesystem.o shell.o
	$(CC) $(CFLAGS) -lreadline -lncurses -o shell shell.o filesystem.o

shell.o: fs_shell.c
	$(CC) $(CFLAGS) -c -o shell.o shell.c

testfs: testfs.o filesystem.o
	$(CC) $(CFLAGS) -o testfs testfs.o filesystem.o

testfs.o: testfs.c
	$(CC) $(CFLAGS) -c -o testfs.o testfs.c

filesystem.o: filesystem.h filesystem.c
	$(CC) $(CFLAGS) -c -o filesystem.o filesystem.c

clean:
	rm -f *.o $(BIN) *~