CC=gcc
CFLAGS=-Wall -std=c99 -g

all: mutate_map swap swap_ends

mutate_map: mutate_map.o
	$(CC) -o $@ $^ $(CFLAGS)

swap: swap.o
	$(CC) -o $@ $^ $(CFLAGS)

swap_ends: swap_ends.o
	$(CC) -o $@ $^ $(CFLAGS)

deref_void: deref_void.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o mutate_map deref_void swap swap_ends
