CC=gcc
CFLAGS=-Wall -std=c99 -g

all: warmup stack_lifo linked_list stack_clobber

warmup: warmup.o
	$(CC) -o $@ $^ $(CFLAGS)

stack_clobber: stack_clobber.o
	$(CC) -o $@ $^ $(CFLAGS)

stack_lifo: stack_lifo.o
	$(CC) -o $@ $^ $(CFLAGS)

linked_list: linked_list.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o warmup stack_lifo linked_list stack_clobber
