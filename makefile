CC=gcc
CFLAGS=-Wall -Werror

.PHONY: clean

all: bin/chess

bin/chess: bin build/main.o build/chess.o
	$(CC) $(CFLAGS) build/main.o build/chess.o -o bin/chess

build/chess.o: build src/chess.c
	$(CC) $(CFLAGS) -c src/chess.c -o build/chess.o

build/main.o: build src/main.o
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build

