CC = mpicc
CFLAGS = -Wall -std=c11
COMPILE = $(CC) $(CFLAGS) -c

skeleton: skeleton.o utils.o
	$(CC) $^ -o $@

skeleton.o: src/skeleton.c
	$(COMPILE) $< -o $@

utils.o: src/utils.c src/utils.h
	$(COMPILE) $< -o $@

clean:
	rm -f *.o skeleton
