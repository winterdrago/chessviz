CC=gcc
CFLAGS=-Wall -Werror

.PHONY: clean

all: bin/chess

test: bin/test
	bin/test

bin/test: bin build/test.o build/chess.o build/moves.o
	$(CC) $(CFLAGS) build/moves.o build/chess.o build/test.o -o bin/test

build/test.o: build src/main.c src/chess.c test/main.c
	$(CC) $(CFLAGS) -I thirdparty -I src -c test/main.c -o build/test.o

bin/chess: bin build/main.o build/chess.o build/moves.o
	$(CC) $(CFLAGS) build/main.o build/chess.o build/moves.o -o bin/chess

build/moves.o: build src/moves.c
	$(CC) $(CFLAGS) -c src/moves.c -o build/moves.o

build/chess.o: build src/chess.c
	$(CC) $(CFLAGS) -c src/chess.c -o build/chess.o

build/main.o: build src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o build/main.o

bin:
	mkdir bin

build:
	mkdir build

clean:
	rm -rf bin build

