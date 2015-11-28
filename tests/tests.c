#include "test.h"
#include "../src/server.h"
#include "../src/structures.h"
#include "../src/functions.h"


void sendRequest(SOCKET sd, char* buffer)
{
    if( send(sd , buffer , strlen(buffer) , 0) == -1)
    {
        fprintf(stderr, "Error when sending message from client\n");
        exit(1);
    }
    printf("Message Send\n");
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in socket;

    socket.sin_family = AF_INET;
    socket.sin_port = htons(3000);
    socket.sin_addr.s_addr = inet_addr("127.0.0.1");

    void *socket_ptr = &socket;
    struct sockaddr *socket_addr = socket_ptr;
    if (connect(sockfd, socket_addr, sizeof(socket)) == -1)
        fprintf(stderr,"Error when connecting client\n");
    char buffer[1024];
    sendRequest(sockfd, "Hello server, how are you ?");
    if((recv(sockfd, buffer, sizeof buffer - 1, 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }

    printf("MESSAGE RECEIVE : %s \n",buffer);



    return 0;
}
