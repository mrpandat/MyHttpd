#include "functions.h"

int main(int argc, char **argv)
{
    struct stat fileStat;
    int resStat;
    int fd = -1;

    struct chint *command = malloc(sizeof(struct chint));
    command->number = -1;
    command->charactere = "";
    struct chint *help = malloc(sizeof(struct chint));
    help->number = -1;
    help->charactere = "";
    struct chint *configFile = malloc(sizeof(struct chint));
    configFile->number = -1;
    configFile->charactere = "";

    struct conf_struct *config = malloc(sizeof(struct conf_struct));

    int errorInOptions = parseOptions(argc, argv, command, configFile, help);
    if (errorInOptions == 1)
    {
        fprintf(stderr, "Error in command line, type %s -h to display help informations\n", argv[0]);
        return 1;
    }

    int helpDisplayed = helpOption(command, configFile, help, argv[0]);
    if (helpDisplayed == 1)
        return 0;

    if (configFile->number != -1)
    {
        fd = open(argv[configFile->number], O_RDONLY);
        resStat = stat(argv[configFile->number], &fileStat);
        if ((fd == -1) || (resStat < 0) || (!S_ISREG(fileStat.st_mode)))
        {
            fprintf(stderr, "Error: unable to open \"%s\" as a file\n", argv[configFile->number]);
            return 2;
        }
        struct conf_struct *config = parseConf(fd);
        if(config->port == 0)
            return 1;
    }
    if(command->number != -1)
    {
        if ((!strcmp(argv[command->number], "reload")) || (!strcmp
                (argv[command->number], "start")) || (!strcmp(argv[command->number], "stop")) || (!strcmp(argv[command->number], "restart")))
        {
        }
        else
        {
            fprintf(stderr, "\"%s\" is not a valid command\n", command->charactere);
            return 1;
        }

        SOCKET listener = socket(AF_INET, SOCK_STREAM, 0);
        if(listener == INVALID_SOCKET)
        {
            perror("socket()");
            exit(errno);
        }

        SOCKADDR_IN sin = { 0 };

        sin.sin_addr.s_addr = htonl(INADDR_ANY);

        sin.sin_family = AF_INET;

        sin.sin_port = htons(config->port);

        if(bind (listener, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
        {
            perror("bind()");
            exit(errno);
        }

        if(listen(listener, 5) == SOCKET_ERROR)
        {
            perror("listen()");
            exit(errno);
        }

        SOCKADDR_IN csin = { 0 };

        SOCKET caller;

        int sinsize = sizeof csin;

        printf("waiting for connection:\n");
        caller = accept(listener, (SOCKADDR *)&csin, (socklen_t *)&sinsize);

        if(caller == INVALID_SOCKET)
        {
            perror("accept()");
            exit(errno);
        }



    }



    return 0;
}

