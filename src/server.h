#ifndef SERVER_H
#define SERVER_H

#include "structures.h"

int initSocket();
void closeSocket(SOCKET socket);
void sendResponse(SOCKET socket, char* buffer);

#endif