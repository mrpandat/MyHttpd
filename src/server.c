#include "server.h"

int checkErrorFile(char* filename)
{
    if( (access( filename, 0 )) != -1 )
    {
        if( (access( filename, R_OK )) == -1 )
            return 403;
        return 200;
    }
    else
    {
        return 404;
    }
}

char* getErrorMessage(int error)
{
    switch(error)
    {
        case (404):
            return "Not Found\n";
        case (403):
            return "Forbidden\n";
        case (200):
            return "OK\n";
        default:
            return "Internal Error";
    }
}


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
        fprintf(stderr, "Error when accepting socket from server\n");
        exit(1);
    }
    printf("Client Accepted...\n");
    char buffer[BUFFER_SIZE];

    ssize_t n = recv(sd_client, buffer, BUFFER_SIZE, 0);
    if(n == -1)
    {
        fprintf(stderr, "Error when receiving message from client\n");
        exit(1);
    }
    buffer[n] = '\0';
    printf("MESSAGE RECEIVE : %s\n\n", buffer);
    sendResponse(sd_client,"I'am fine thank you\n");

}

void receiveMessage(SOCKET sd, struct sockaddr *server)
{

    if (listen(sd, 1) < 0)
        fprintf(stderr,"Error while listnening ");
    printf("Now listening...\n");

    acceptClient(sd, server);
    closesocket(sd);
}


void initSocket(struct conf_struct *config)
{
    struct sockaddr_in server;


    int sd = socket(AF_INET , SOCK_STREAM , 0);
    if (sd == -1)
        printf("Could not create socket");
    int bool = 1;
    setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&bool,sizeof(int));

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons( config->port );

    void* sever_ptr = &server;
    struct sockaddr *server_cast = sever_ptr;


    if(bind(sd, server_cast ,sizeof(server)) == -1)
    {
        fprintf(stderr,"Error when binding socket\n");
        exit(1);
    }
    printf("Connected\n");
    receiveMessage(sd, server_cast);

    printf("Code : %d", checkErrorFile("README"));
    shutdown(sd,2);
    close(sd);
}