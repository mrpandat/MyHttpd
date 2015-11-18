#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>


int parseOptions(int argc, char **argv);

void displayHelp(void);

#endif /* !FUNCTIONS_H */