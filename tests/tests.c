#include "test.h"
#include "../src/server.h"
#include "../src/structures.h"
#include "../src/functions.h"


int main()
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in that;

    memset(&that,0,sizeof(that)); /* en System V */
    that.sin_family = AF_INET;
    that.sin_port = htons(3000);
    that.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sockfd, &that, sizeof(that)) < 0) /* error */
        fprintf(stderr,"Error when connecting client");

    return 0;
}
