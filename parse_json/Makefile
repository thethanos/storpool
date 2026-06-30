.PHONY: all clean

CC := gcc

SRC := src
INCLUDE := include
DEPS := deps

CFLAGS := -I$(INCLUDE) -I$(DEPS) -O3 -Wall -Wextra #-fsanitize=address
LDFLAGS := #-fsanitize=address


all: reader

reader: main.o hash_table.o
	$(CC) $(LDFLAGS) main.o hash_table.o -o reader

main.o: $(SRC)/main.c $(INCLUDE)/hash_table.h $(DEPS)/jsmn.h $(DEPS)/uthash.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o main.o

hash_table.o: $(SRC)/hash_table.c $(INCLUDE)/hash_table.h $(DEPS)/uthash.h
	$(CC) $(CFLAGS) -c $(SRC)/hash_table.c -o hash_table.o

clean:
	rm -f main.o hash_table.o reader