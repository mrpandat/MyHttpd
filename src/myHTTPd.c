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

    struct conf_struct *config = NULL;

    int errorInOptions = parseOptions(argc, argv, command, configFile, help);
    if (errorInOptions == 1)
    {
        fprintf(stderr, "Error in command line, type %s -h to display help"
                " informations\n", argv[0]);
        return 1;
    }

    int helpDisplayed = helpOption(command, configFile, help, argv[0]);
    if (helpDisplayed == 1)
    {
        free(command);
        free(help);
        free(configFile);
        return 0;
    }

    if (configFile->number != -1)
    {
        fd = open(argv[configFile->number], O_RDONLY);
        resStat = stat(argv[configFile->number], &fileStat);
        if ((fd == -1) || (resStat < 0) || (!S_ISREG(fileStat.st_mode)))
        {
            fprintf(stderr, "Error: unable to open \"%s\" as a file\n",
                argv[configFile->number]);
            free(command);
            free(help);
            free(configFile);
            return 2;
        }
        config = parseConf(fd);
        if (config->port == 0)
        {
            free(command);
            free(help);
            free(configFile);
            return 1;
        }
    }
    if (command->number != -1)
    {
        if ((!strcmp(argv[command->number], "reload")) ||
            (!strcmp(argv[command->number], "start")) ||
            (!strcmp(argv[command->number], "stop")) ||
            (!strcmp(argv[command->number], "restart")))
        {
            free(help);
            return execCommand(argc, argv, command, config, configFile);

        }
        else
        {
            fprintf(stderr, "\"%s\" is not a valid command\n",
                command->charactere);
            return 1;
        }
    }



    return 0;
}

