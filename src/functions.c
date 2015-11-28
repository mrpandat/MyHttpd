#include "functions.h"

void displayHelp(char *binary)
{
    printf("Usage: %s { -h | -f file [-a start|stop|restart|reload] }\n",
    basename(binary));
    printf("  -f file    use `file' as configuration file\n");
    printf("  -h         display this help and exit\n");
    printf("  -a action  perform `action' on daemon\n");
}

int parseOptions(int argc,char **argv, struct chint *command,
    struct chint *configFile, struct chint *help)
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

int helpOption(struct chint *command, struct chint *configFile,
struct chint *help, char *binary)
{
    if((help->number != configFile->number) && (help->number != command->number)
        && (help->number != -1))
    {
        displayHelp(binary);
        return 1;
    }
    return 0;

}

void fillStruct(char* buffer,char* buffer2, size_t k, struct conf_struct
*conf_file)
{
    size_t j = 0;
    char* buffer3 = calloc(BUFFER_SIZE, sizeof(char));
    for (size_t i = k; i < BUFFER_SIZE; i++) {
        if (buffer[i] == '\n'|| buffer[i] == '\0') {
            if(strcmp(buffer2,"port") == 0)
                conf_file->port = atoi(buffer3);
            else if (strcmp(buffer2,"root-dir") == 0)
            {
                conf_file->rootDir = malloc(sizeof(buffer3));
                strcpy(conf_file->rootDir, buffer3);
            }
            else if (strcmp(buffer2,"pid-file") == 0)
            {
                conf_file->pidFile = malloc(sizeof(buffer3));
                strcpy(conf_file->pidFile, buffer3);
            }
            else if (strcmp(buffer2,"log-file") == 0)
            {
                conf_file->logFile = malloc(sizeof(buffer3));
                strcpy(conf_file->logFile,buffer3);
            }
            free(buffer3);
            return;
        }
        if (buffer[i] != ' ' && buffer[i] != '=')
        {
            buffer3[j] = buffer[i];
            j++;
        }
    }
}

int checkErrorConf(int fd)
{
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    int line = 1;
    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        for (size_t i = 0; i < BUFFER_SIZE; i++)
        {
            if(buffer[i] == '\n')
                line++;
            else if(buffer[i] == '=')
            {
                if(buffer[i-1] != ' ' || buffer[i+1] != ' ')
                {
                    fprintf(stderr, "Error of syntax in the conf file at line "
                            "%d \n", line);
                    free(buffer);
                    return 1;
                }
            }
        }
    }
    free(buffer);
    return 0;
}

struct conf_struct *parseConf(int fd)
{
    struct conf_struct *conf_file = malloc(sizeof(struct conf_struct));
    if(checkErrorConf(fd) == 1)
        return conf_file;
    lseek(fd, 0, 0);
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    char* buffer2 = calloc(BUFFER_SIZE, sizeof(char));
    int j = 0;
    while (read(fd, buffer, BUFFER_SIZE) > 0)
    {
        for (size_t i = 0; i < BUFFER_SIZE; i++)
        {
            if(buffer[i] == '\n')
            {
                memset(buffer2, 0, BUFFER_SIZE);
                j = 0;
            }
            else if(buffer[i] == '=')
            {
                fillStruct(buffer, buffer2, i, conf_file);
                memset(buffer2, 0, BUFFER_SIZE);
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

int execCommand(int argc, char **argv, struct chint *command, struct conf_struct *config, struct chint *configFile)
{
    if(!strcmp(argv[command->number], "start"))
    {
        initSocket(config);
        free(config);
    }
    else if(!strcmp(argv[command->number], "reload"))
    {
        struct stat fileStat;
        int fd = open(argv[configFile->number], O_RDONLY);
        int resStat = stat(argv[configFile->number], &fileStat);
        if ((fd == -1) || (resStat < 0) || (!S_ISREG(fileStat.st_mode)))
        {
            fprintf(stderr, "Error: unable to open \"%s\" as a file\n",
            argv[configFile->number]);
            return 2;
        }
        config = parseConf(fd);
        if(config->port == 0)
            return 1;
        close(fd);
        initSocket(config);
        free(config);
    }
    else if(!strcmp(argv[command->number], "stop"))
    {
        return 0;
    }
    else
    {
        printf("restarting...\n");
        char *commandLine = malloc(BUFFER_SIZE);
        commandLine = argv[0];   
        char *strSpace = " ";
        for(int i = 1; i < argc; i++)
        {
            if(!strcmp(argv[i], "restart"))
                argv[i] = "start";
            char *temp = malloc(BUFFER_SIZE);
            temp = strcpy(temp,argv[i]);
            commandLine = strcat(commandLine, strSpace);
            commandLine = strcat(commandLine, temp); 
            free(temp);
        }
        int status = system(commandLine);
        free(commandLine);
        if(!WIFEXITED(status))
            return 0;
        else return WEXITSTATUS(status);
    }
    return 0;
}
