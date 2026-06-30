.PHONY: all clean

LD := ld
ASM := as



start: main.o
	$(LD) main.o -o start

main.o: main.s
	$(ASM) main.s -o main.o

clean:
	rm -f main.o start