CC=gcc
CFLAGS= -Wall -m32 -std=gnu11 -lpthread
DEPS = monitor.h
OBJ = monitor.o
MAIN = sleepingStylistMon.c

.PHONY: run
run: clean stylistMon
	./stylistSem > output.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stylistMon: $(OBJ)
	$(CC) $(MAIN) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o output.txt stylistMon