.PHONY: all clean test

CC := gcc

INCLUDE := include
SRC := src

CFLAGS := -I$(INCLUDE) -O3 -Wall -Wextra
LDFLAGS := -fsanitize=address

all: counter test_process_buffer

counter: main.o process_buffer.o
	$(CC) $(LDFLAGS) main.o process_buffer.o -o counter

test_process_buffer: test_process_buffer.o process_buffer.o
	$(CC) $(LDFLAGS) test_process_buffer.o process_buffer.o -o test_process_buffer

test_process_buffer.o: $(SRC)/test_process_buffer.c $(INCLUDE)/process_buffer.h
	$(CC) $(CFLAGS) -c $(SRC)/test_process_buffer.c

main.o: $(SRC)/main.c $(INCLUDE)/process_buffer.h
	$(CC) $(CFLAGS) -c $(SRC)/main.c

process_buffer.o: $(SRC)/process_buffer.c $(INCLUDE)/process_buffer.h
	$(CC) $(CFLAGS) -c $(SRC)/process_buffer.c

clean:
	rm -f *.o test_process_buffer counter

test: test_process_buffer
	./test_process_buffer