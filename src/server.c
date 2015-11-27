#include "server.h"


void sendResponse(SOCKET sd, char* buffer)
{
    if( send(sd , buffer , strlen(buffer) , 0) == -1)
    {
        fprintf(stderr, "Error when sending message from server\n");
        exit(1);
    }
    printf("Message Send\n");
}


void acceptClient(SOCKET sd, struct sockaddr *server)
{
    socklen_t size = sizeof(server);

    int sd_client = accept(sd, server, &size);
    if(sd_client == -1)
    {
        fprintf(stderr, "Error when accepting sockect from server\n");
        exit(1);
    }
    printf("Client Accepted...\n");
    sendResponse(sd_client, "Welcome user");

}

void receiveMessage(SOCKET sd, struct sockaddr *server)
{

    while(1)
    {
        if (listen(sd, 5) < 0)
            fprintf(stderr,"Error while listnening ");
        printf("Now listening...\n");

        acceptClient(sd, server);
    }

}


int initSocket()
{
    struct sockaddr_in server;


    int sd = socket(AF_INET , SOCK_STREAM , 0);
    if (sd == -1)
        printf("Could not create socket");

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons( 3000 );

    void* sever_ptr = &server;
    struct sockaddr *server_cast = sever_ptr;


    if(bind(sd, server_cast ,sizeof(server)) == -1)
    {
        fprintf(stderr,"Error when binding socket\n");
        return -1;
    }

    printf("Connected\n");
    receiveMessage(sd, server_cast);
    return sd;
}

void closeSocket(SOCKET socket)
{
    closesocket(socket);
}
