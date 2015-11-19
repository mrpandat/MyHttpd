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

/*
void* parseConf(int fd)
{
    lseek(fd, 0, 0);
    int j = 0;
    int current_line = 0;
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        for (int i = 0; i < BUFFER_SIZE; i++)
        {

        }
    }

}*/
