#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <libgen.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
#define BUFFER_SIZE 1024
#define _GNU_SOURCE

/**
 * structure used to save informations about arguments passed in command line
 */
struct chint {
	int number;
	char *charactere;
};


/**
 * strucure used to save the server's configuration
 */
struct conf_struct {
	int port;
	char* rootDir;
	char* pidFile;
	char *logFile;
};

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif /* !STRUCTURE_H */