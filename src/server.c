#include "server.h"


void launchApp(uint16_t port) {


    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener == -1) {
        perror("socket()");
    }

    struct sockaddr_in *sin = malloc(sizeof(struct sockaddr_in));

    sin->sin_addr.s_addr = htonl(INADDR_ANY);

    sin->sin_family = AF_INET;

    sin->sin_port = htons(port);

    /*
    void* sin_ptr = sin;
    struct sockaddr *sock_addr = sin_ptr;
    if (bind(listener, sock_addr, sizeof sin) == -1) {
        perror("bind()");
    }

     */
    if (listen(listener, 5) == -1) {
        perror("listen()");
    }

    struct sockaddr_in *csin = {0};
    void* csin_ptr = csin;
    struct sockaddr *sock_addr_connect = csin_ptr;

    int caller;

    socklen_t sinsize = sizeof csin;

    printf("waiting for connection:\n");
    caller = accept(listener, sock_addr_connect,  &sinsize);

    if (caller == -1) {
        perror("accept()");
    }

    free(sin);

}
