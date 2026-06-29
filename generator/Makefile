CC := gcc

.PHONY: all clean

all: generator

generator: main.o
	$(CC) main.o -o generator

main.o: main.c
	$(CC) -c main.c -o main.o

clean:
	rm -rf main.o generator