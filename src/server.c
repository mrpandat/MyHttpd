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
        case (200):
            return "OK\n";
        case (400):
            return "Bad Request\n";
        case (403):
            return "Forbidden\n";
        case (404):
            return "Not Found\n";
        case (405):
            return "Method Not Allowed\n";
        case (501):
            return "Internal Server Error\n";
        default:
            return "Internal Error";
    }
}

int checkErrorRequest(struct requestHttp *request)
{
    char buffer[1024];
    for(size_t i = 0; i < sizeof(request->version); i++)
        buffer[i] = request->version[i];
    for(size_t i = 0; i < sizeof(buffer); i++)
        request->version[i] = buffer[i] ;
    if( (strcmp(request->version,"HTTP/1.0") == 0) ||
                (strcmp(request->version, "HTTP/1.1")) == 0)
    {
        if(strcmp("GET", request->get) == 0)
        {
            return 200;
        }
        if( strcmp(request->version,"HTTP/1.0") == 0 &&
                ((strcmp("HEAD",request->get) == 0)
                 || (strcmp("POST", request->get) == 0)))
        {
            return 501;

        }
        else if( strcmp(request->version,"HTTP/1.1") == 0 && (
                (strcmp("PUT",request->get) == 0) ||
                (strcmp("TRACE",request->get) == 0) ||
                (strcmp("UPDATE",request->get) == 0) ||
                (strcmp("DELETE", request->get) == 0)))
            return 501;
        else
            return 405;

    }
    else
        return 400;
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
    struct requestHttp *request = fillRequest(buffer);

    struct responseHttp *response= malloc(sizeof(struct responseHttp));
    response->http_version = request->version;
    response->http_code = "200";
    response->http_message = "OK\n";
    /*char P[9];
    char A[9];
 
    _strtime(P);
    _strdate(A);
 
    printf ("Nous sommes le %s et il est %s\n\n",A,P);*/
    response->date = "Date: Mon, 13 Oct 2015 13:17:20 GMT\n";
    response->server_info = "Server: myHTTPD: 1.0\n";
    response->content_type = "Content -type: text/html\n\n";
    response->body = "<h1>MyHTTPd</h1\n";
    char *buftemp = fillBufferWithStruct(response);
    printf("Code HTTP: %d\n", checkErrorRequest(request));
    printf("Code FILE : %d\n", checkErrorFile(request->file));
    free(request->file);
    free(request->get);
    free(request->version);
    free(request);
    sendResponse(sd_client, buftemp);
    free(buftemp);
}

char *fillBufferWithStruct(struct responseHttp *response)
{
    char *buffer = malloc(1024);
    snprintf(buffer, 1024, "%s%s%s%s%s%s%s", response->http_version, response->http_code, response->http_message, response->date, response->server_info, response->content_type, response->body);
    return buffer;
}

void receiveMessage(SOCKET sd, struct sockaddr *server)
{

    if (listen(sd, 1) < 0)
        fprintf(stderr,"Error while listnening");
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

    shutdown(sd,2);
    close(sd);
    free(config->rootDir);
    free(config->pidFile);
    free(config->logFile);
    free(config);
}

struct requestHttp *fillRequest(char *buffer)
{
    struct requestHttp *request = malloc(sizeof(struct requestHttp));
    char *line = malloc(BUFFER_SIZE);
    request->file = malloc(BUFFER_SIZE);
    request->version = malloc(BUFFER_SIZE);
    request->get = malloc(BUFFER_SIZE);
    int i = 0;
    while (buffer[i] != '\n')
    {
        line[i] = buffer[i];
        i++;
    }
    
    int j = 0;
    int x = 0;
    while(line[x] != ' ')
    {
        request->get[j] = line[x];
        x++;
        j++;
    }
    request->get[j] = '\0';
    x++;
    j = 0;
    while(line[x] != ' ')
    {
        request->file[j] = line[x];
        x++;
        j++;
    }
    request->file[j] = '\0';
    x++;
    j = 0;
    while(line[x] != '\n')
    {
        request->version[j] = line[x];
        x++;
        j++;
    }
    return request;

}