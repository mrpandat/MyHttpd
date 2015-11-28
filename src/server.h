#ifndef SERVER_H
#define SERVER_H

#include "structures.h"

void initSocket(struct conf_struct *config);

void closeSocket(SOCKET socket);

void sendResponse(SOCKET socket, char* buffer);

char *fillBufferWithStruct(struct responseHttp *response);

struct responseHttp *fillRequest(char *buffer);

#endif