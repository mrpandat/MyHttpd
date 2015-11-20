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

void resetArray(char* array, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        array[i] = '\0';
    }
}

int myStrcmp(char* array, char*array2, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        if (array[i] != array2[i])
            return 1;
    }
    return 0;
}

size_t BUFFER_SIZE = 1024;

void filleStruct(char* buffer,char* buffer2, size_t k, struct conf_struct
*conf_file)
{
    size_t j = 0;

    char* buffer3 = calloc(BUFFER_SIZE, sizeof(char));
    for (size_t i = k; i < BUFFER_SIZE; i++) {
        if (buffer[i] == '\n'|| buffer[i] == '\0') {
            if(myStrcmp(buffer2,"port",4) == 0)
                conf_file->port = atoi(buffer3);
            if(myStrcmp(buffer2,"root-dir",9) == 0)
                conf_file->rootDir = buffer3;
            if(myStrcmp(buffer2,"pid-file",8) == 0)
                conf_file->pidFile = buffer3;
            if(myStrcmp(buffer2,"log-file",8) == 0)
                conf_file->logFile = buffer3;
            free(buffer3);
            return;
        }
        if (buffer[i] != ' ' && buffer[i] != '=') {
            buffer3[j] = buffer[i];
            j++;
        }
    }
}
struct conf_struct * parseConf(int fd)
{
    struct conf_struct *conf_file = malloc(sizeof(struct conf_struct));
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    char* buffer2 = calloc(BUFFER_SIZE, sizeof(char));
    int j = 0;
    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        for (size_t i = 0; i < BUFFER_SIZE; i++)
        {
            if(buffer[i] == '\n')
            {
                resetArray(buffer2, BUFFER_SIZE);
                j = 0;
            }
            else if(buffer[i] == '=')
            {
                filleStruct(buffer, buffer2, i, conf_file);
                resetArray(buffer2, BUFFER_SIZE);
            }
            else if(buffer[i] != ' ')
            {
                buffer2[j] = buffer[i];
                j++;
            }
        }
    }
    free(buffer);
    free(buffer2);
    return conf_file;
}