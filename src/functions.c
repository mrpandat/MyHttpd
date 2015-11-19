#include "functions.h"

/**
 * function displaying help
 */
void displayHelp(void)
{
    printf("Usage: myHTTPd { -h | -f file [-a start|stop|restart|reload] }\n");
    printf("-f file    use `file' as configuration file\n");
    printf("-h         display this help and exit\n");
    printf("-a action  perform `action' on daemon\n");
}

/**
 * function for saving command, configuration file and/or help option given as argument in command line
 */
int parseOptions(int argc,char **argv, struct chint *command, struct chint *configFile, struct chint *help)
{
    for(int i = 1; i < argc; i++)
    {
        if((!strcmp(argv[i], "-h")) && (help->number == -1))
        {
            help->number = i;
            help->charactere = "-h";
        }
        else if((!strcmp(argv[i], "-f")) && (configFile->number == -1))
        {
            if(i+1 < argc)
            {
                configFile->number = i+1;
                configFile->charactere = argv[i+1];
            }
            else
                return 1;
        }
        else if((!strcmp(argv[i], "-a")) && (command->number == -1))
        {
            if(i+1 < argc)
            {
                command->number = i+1;
                command->charactere = argv[i+1];
            }
            else
                return 1;
        }
    }
    return 0;
}

/**
 * functions checking if help has to be displayed.
 */
int helpOption(struct chint *command, struct chint *configFile, struct chint *help)
{
    if((help->number != configFile->number) && (help->number != command->number) && (help->number != -1))
    {
        displayHelp();
        return 1;
    }

    return 0;
}