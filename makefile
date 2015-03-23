CC=gcc
CFLAGS=-Wall -g -std=c99
SRC=./src
BIN=./bin

all: mon

mon: $(SRC)/mon.c $(SRC)/mon.h watcher
	$(CC) $(CFLAGS) $(BIN)/watcher.o $(SRC)/mon.c $(SRC)/mon.h -o mon

debug: $(SRC)/mon.c $(SRC)/mon.h
	$(CC) $(CFLAGS) -DDEBUG  $(SRC)/mon.c $(SRC)/mon.h -o mon

watcher: $(SRC)/watcher.c $(SRC)/watcher.h
	$(CC) $(CFLAGS) -c $(SRC)/watcher.c -o $(BIN)/watcher.o

clean:
	rm mon $(BIN)/watcher.o