.PHONY: all clean

CC := gcc

SRC := src
INCLUDE := include
DEPS := deps

CFLAGS := -I$(INCLUDE) -I$(DEPS) -O3 -Wall -Wextra -Wstrict-prototypes -fsanitize=address
LDFLAGS := -fsanitize=address


all: processor test_counter

processor: main.o counter.o
	$(CC) $(LDFLAGS) main.o counter.o -o processor

test_counter: test_counter.o
	$(CC) $(LDFLAGS) test_counter.o -o test_counter

test_counter.o: $(SRC)/test_counter.c
	$(CC) $(CFLAGS) -c $(SRC)/test_counter.c -o test_counter.o

main.o: $(SRC)/main.c $(INCLUDE)/counter.h $(DEPS)/jsmn.h 
	$(CC) $(CFLAGS) -c $(SRC)/main.c -o main.o

counter.o: $(SRC)/counter.c $(INCLUDE)/counter.h $(DEPS)/uthash.h
	$(CC) $(CFLAGS) -c $(SRC)/counter.c -o counter.o

clean:
	rm -f main.o counter.o test_counter.o processor test_counter

test: test_counter
	./test_counter