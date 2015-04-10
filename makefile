CC=gcc
CFLAGS=-Wall -g -std=c99
SRC=./src
BIN=./bin

.PHONY: clean mkdir

all: mkdir mon 

mon: $(SRC)/mon.c $(SRC)/mon.h watcher runner
	$(CC) $(CFLAGS) $(BIN)/watcher.o $(BIN)/runner.o $(SRC)/mon.c $(SRC)/mon.h -o mon

debug: $(SRC)/mon.c $(SRC)/mon.h watcher runner
	$(CC) $(CFLAGS) -DDEBUG $(BIN)/watcher.o $(BIN)/runner.o $(SRC)/mon.c $(SRC)/mon.h -o mon

watcher: $(SRC)/watcher.c $(SRC)/watcher.h
	$(CC) $(CFLAGS) -c $(SRC)/watcher.c -o $(BIN)/watcher.o

runner:	$(SRC)/runner.c $(SRC)/runner.h
	$(CC) $(CFLAGS) -c $(SRC)/runner.c -o $(BIN)/runner.o

mkdir:
	mkdir -p $(BIN)


clean:
	rm -r $(BIN) || rm mon
