#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./myhttpd.h"


int openFile(char *filename)
{
    int fd = open(filename, O_RDONLY);
    struct stat *file = calloc(BUFFER_SIZE, sizeof(struct stat));
    int result_stat = stat(filename, file);
    if (!S_ISREG(file->st_mode) || result_stat == -1)
    {
        if(fd < 0)
            printf("Error while opening file %s \n", filename);
        free(file);
        return -1;
    }
    free(file);
    return fd;
}
