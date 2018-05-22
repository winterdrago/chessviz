CC=gcc
CFLAGS=-Wall -Werror

all: bin/chess

bin/chess: bin build/chess.o
	$(CC) $(CFLAGS) build/chess.o -o bin/chess

build/chess.o: build src/chess.c
	$(CC) $(CFLAGS) -c src/chess.c -o build/chess.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build

