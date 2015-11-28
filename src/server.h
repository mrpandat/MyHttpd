#ifndef SERVER_H
#define SERVER_H

#include "structures.h"

/**
 * function initializing a socket
 */
void initSocket(struct conf_struct *config);

/**
 * function sending response to client
 */
void sendResponse(SOCKET socket, char* buffer);

/*
 * function filling a new buffer with given structure informations
 */
char *fillBufferWithStruct(struct responseHttp *response);

/**
 * function filling request structure with given buffer informations
 */
struct requestHttp *fillRequest(char *buffer);

#endif