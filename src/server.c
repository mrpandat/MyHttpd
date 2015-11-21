#include "server.h"


int openSocket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
    {
        fprintf(stderr, "Error when creating socket..\n");
        return -1;
    }
    return sock;

}


void connectSocket()
{
/*
    struct hostent *host = gethostbyname("localhost");

    if(host == NULL)
    {
        fprintf(stderr, "Error when getting infos from the host..\n");
        return;
    }

    struct sockaddr_in *sock = malloc(sizeof(struct sockaddr_in));

    void* host_addr = host->h_addr_list[0];
    struct in_addr *address = host_addr;

    sock->sin_addr = *address;
    sock->sin_port = port;
    sock->sin_family = AF_INET;

    void* struct_ptr = sock;
    struct sockaddr* sock_struct = struct_ptr;
    if(connect(openSocket(), sock_struct, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "Error when connecting the socket..\n");
        return;
    }


    return;
    */
}
