#ifndef STRUCTURE_H
# define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

struct chint {
	int number;
	char *charactere;
};


struct conf_struct
{
	int port;
	char* rootDir;

	int pidFile;
	char *logFile;
};

size_t BUFFER_SIZE = 1024;


#endif /* !STRUCTURE_H */