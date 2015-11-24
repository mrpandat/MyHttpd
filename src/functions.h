#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "structures.h"
#include "server.h"

/**
 * Function reading all options in command line and filling structures to save
 * informations given as arguments
 */
int parseOptions(int argc, char **argv, struct chint *command,
struct chint *configFile, struct chint *help);

/**
 * function displaying the help summary.
 */
void displayHelp(char *binary);

/**
 * function chosing if help summary has to be displayed
 */
int helpOption(struct chint *command, struct chint *configFile,
struct chint *help, char *binary);

/**
 * function reading the configuration file and filling a structure to save 
 * informations
 */
struct conf_struct *parseConf(int fd);

/**
 * function checking if there is any error in the configuration file
 */
int checkErrorConf(int fd);

/**
 * function filling confStruct with the configuration file's informations
 */
void fillStruct(char* buffer,char* buffer2, size_t k, struct conf_struct
*conf_file);


#endif /* !FUNCTIONS_H */