#include "server.h"


void launchApp(uint16_t port)
{
    int my_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(my_socket == SOCKET_ERROR)
        perror("Create socket");
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    void* address_ptr = &address;
    struct sockaddr *sockaddr_f = address_ptr;
    if(bind(my_socket, sockaddr_f , sizeof(address)) <= INVALID_SOCKET) {
        perror("Error");
        exit(-1);
    }
    if (listen(my_socket, 5) == -1)
        fprintf(stderr, "Error while listening to the connection");
    struct sockaddr_in *csin = {0};
    void* csin_ptr = csin;
    struct sockaddr *sock_addr_connect = csin_ptr;
    socklen_t sinsize = sizeof csin;
    printf("waiting for connection:\n");
    int caller = accept(my_socket, sock_addr_connect,  &sinsize);
    if (caller == -1)
        fprintf(stderr, "Error while launching accept()");

}
