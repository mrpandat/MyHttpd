CC = gcc
CFLAGS = -pedantic -std=c99 -Werror -Wall -Wextra
OBJS = functions.o myHTTPd.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o myHTTPd

clean:
	rm -f *.o
	rm -f myHTTPd
