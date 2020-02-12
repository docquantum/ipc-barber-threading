CC=gcc
CFLAGS= -Wall -std=c11 -lpthread
DEPS = monitor.h
OBJ = monitor.o
MAIN = sleepingStylistMon.c

.PHONY: run
run: clean stylistMon
	./stylistMon > output.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

stylistMon: $(OBJ)
	$(CC) $(MAIN) -o $@ $^ $(CFLAGS)

clean:
	rm -f *~ *.o output.txt stylistMon