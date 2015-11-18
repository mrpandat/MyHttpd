#include "functions.h"

void displayHelp(void)
{
    printf("Usage: myHTTPd { -h | -f file [-a start|stop|restart|reload] }\n");
    printf("-f file    use `file' as configuration file\n");
    printf("-h         display this help and exit\n");
    printf("-a action  perform `action' on daemon\n");
}

int parseOptions(int argc, char **argv)
{
    for(int i = 1; i < argc; i++)
    {
        if (!strcmp("-h",argv[i]))
        {
            if (!strcmp("-f", argv[i-1]))
                return i;
            displayHelp();
            return 0;
        }
    }
    for(int i = 1; i < argc; i++)
    {
        if (!strcmp("-f", argv[i]))
        {
            return i+1;
        }
    }
    return -1;
}
