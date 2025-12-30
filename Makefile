CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/datastore.c
OUT = build/kvstore

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -rf build