CC = gcc
CFLAGS = -pedantic -std=c99  -Wall -Wextra
OBJS = tests.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test

clean:
	rm -f *.o
	rm -f test

check: all 
	./test
