CC=gcc
CFLAGS= -Wall -std=c11 -lpthread
DEPS =
OBJ =

.PHONY: run
run: clean stylistSem
	./stylistSem > output.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stylistSem: $(OBJ)
	$(CC) sleepingStylistSem.c -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o output.txt stylistSem