#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"

int parseOptions(int argc, char **argv, struct chint *command, struct chint *configFile, struct chint *help);

void displayHelp(char *binary);

int helpOption(struct chint *command, struct chint *configFile, struct chint *help, char *binary);

struct conf_struct * parseConf(int fd);

#endif /* !FUNCTIONS_H */