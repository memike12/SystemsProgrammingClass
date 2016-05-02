
CC=clang
CFLAGS=-Wall

BIN=swap save recall mycp mywc mycat

all: $(BIN)

swap: swap.c
	$(CC) $(CFLAGS) swap.c -o swap

save: save.c
	$(CC) $(CFLAGS) save.c -o save

recall: recall.c
	$(CC) $(CFLAGS) recall.c -o recall

mycp: mycp.c
	$(CC) $(CFLAGS) mycp.c -o mycp

mycat: mycat.c
	$(CC) $(CFLAGS) mycat.c -o mycat

mywc: mywc.c
	$(CC) $(CFLAGS) mywc.c -o mywc

clean:
	rm -f $(BIN) *~ a.out