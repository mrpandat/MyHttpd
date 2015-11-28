#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
#include <sys/wait.h>
#include <time.h>


/**
 * define a meaningfull name for the socket binding error result
 */
#define INVALID_SOCKET -1

/**
 * define a meaningfull name for the socket creation error result
 */
#define SOCKET_ERROR -1

/**
 * changing name function from close to close socket to be meaningfull
 */
#define closesocket(s) close(s)

/**
 * define a size for all personnal buffers in the project
 */
#define BUFFER_SIZE 1024

/**
 * access to nonstandard GNU/Linux extension functions
 */
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
    uint16_t port;
    char* rootDir;
    char* pidFile;
    char *logFile;
};

/**
 * structure containing some HTTP response informations
 */
struct responseHttp {
    char *http_version;
    char *http_code;
    char *http_message;
    char *date;
    char* server_info;
    char* content_type;
    char* body;
}__attribute__((packed));

/**
 * structure containing some HTTP request informations
 */
struct requestHttp {
    char *get;
    char *file;
    char *version;
};

/**
 * changing type name 'int' to 'socket' to recognize socket's identifier
 */
typedef int SOCKET;

#endif /* !STRUCTURE_H */