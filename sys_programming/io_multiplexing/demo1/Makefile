OBJS = *.c
CC = gcc
CFLAGS = -Wall -O2
a.out:$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -static -luv -lpthread
clean:
	rm a.out
