#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024;

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
struct conf_struct
{
	int port;
	char* rootDir;
	char* pidFile;
	char *logFile;
};

#endif /* !STRUCTURE_H */