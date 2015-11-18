#include "functions.h"

int main(int argc, char **argv, char **envp)
{
    struct stat fileStat;
    int resStat;
    int fd = -1;
    envp = envp;

    /*if(argc == 1)
    {
        fd = openStdMakeFiles();
        if(fd == -1)
        {
            printf("Error: \"makefile\" or \"Makefile\": no such file\n");
            return 1;
        }
    }
    else
    {*/
        int options = parseOptions(argc, argv);
        if(options == 0)
            return 0;
        else if(options != -1)
        {
            fd = open(argv[options], O_RDONLY);
            resStat = stat(argv[options], &fileStat);
            if((fd == -1) || (resStat < 0) || (!S_ISREG(fileStat.st_mode)))
            {
                printf("Error: unable to open \"%s\" as a file\n", argv[options]);
                return 1;
            }
        }
        /*else if(options == -1)
        {
            fd = openStdMakeFiles();
            if(fd == -1)
            {
                printf("Error: \"makefile\" or \"Makefile\": no such file\n");
                return 1;
            }
        }
    }*/

    return 0;
}
