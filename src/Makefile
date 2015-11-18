CC = gcc
CFLAGS = -std=c99 -g -pedantic -Wextra -Wall -Werror -fpic
SRC=config.o

all :myhttpd.so

myhttpd.so:$(SRC)
	$(CC) $(CFLAGS) -shared $(SRC) -o ../myhttpd.so

clean:
	rm *.o
	rm ../*.so
