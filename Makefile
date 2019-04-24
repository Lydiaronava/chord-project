CC = gcc
CFLAGS = -Wall -std=c11
COMPILE = $(CC) $(CFLAGS) -c

utils.o: src/utils.c src/utils.h
	$(COMPILE) $< -o $@

clean:
	rm -f *.o
