#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

/**
 * function creating the receiver socket, waiting for a connection
 */
void launchApp(uint16_t port);