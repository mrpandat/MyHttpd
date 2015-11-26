CC = gcc
CFLAGS = -pedantic -std=c99 -Werror -Wall -Wextra
OBJS = functions.o myHTTPd.o server.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ../myHTTPd

clean:
	rm -f *.o
	rm -f ../myHTTPd
	rm -rf ../doc
	rm -rf ../tests/*.o
	rm -rf myHTTPd
	rm -rf ../tests/test

doc:
	doxygen
