#include "server.h"

char* checkErrorFile(char* filename)
{
    if( (access( filename, 0 )) != -1 )
    {
        if( (access( filename, R_OK )) == -1 )
            return "403";
        struct stat fileStat;
        int fd = open(filename, O_RDONLY);
        int resStat = stat(filename, &fileStat);
        if ((fd == -1) || (resStat < 0) || (!S_ISREG(fileStat.st_mode)))
            return "406";
        else
            return "200";
    }
    else
        return "404";
}

char* getErrorMessage(char* error)
{

    if (!strcmp("200",error))
        return "OK\n";
    if (!strcmp("400",error))
        return "Bad Request\n";
    if (!strcmp("403",error))
        return "Forbidden\n";
    if (!strcmp("404",error))
        return "Not Found\n";
    if (!strcmp("405",error))
        return "Method Not Allowed\n";
    if (!strcmp("406",error))
        return "Not Acceptable\n";
    if (!strcmp("501",error))
        return "Internal Server Error\n";
    return "Internal Error";
}

char* checkErrorRequest(struct requestHttp *request)
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
            return "200";
        }
        if( strcmp(request->version,"HTTP/1.0") == 0 &&
                ((strcmp("HEAD",request->get) == 0)
                 || (strcmp("POST", request->get) == 0)))
        {
            return "501";

        }
        else if( strcmp(request->version,"HTTP/1.1") == 0 && (
                (strcmp("PUT",request->get) == 0) ||
                (strcmp("TRACE",request->get) == 0) ||
                (strcmp("UPDATE",request->get) == 0) ||
                (strcmp("DELETE", request->get) == 0)))
            return "501";
        else
            return "405";

    }
    else
        return "400";
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
    response->http_code =  checkErrorFile(request->file);
    if(!strcmp(checkErrorFile(request->file), "200"))
        response->http_code =checkErrorRequest(request);

    response->http_message = getErrorMessage(response->http_code);

    time_t timestamp;
    struct tm *t;

    timestamp = time(NULL);
    t = localtime(&timestamp);
    char *date = malloc(BUFFER_SIZE);
    char *format = "%a, %d %b %Y %X %Z";
    strftime(date, BUFFER_SIZE, format, t);
    printf("DATE: %s\n", date);
    response->date = date;
    response->server_info = "Server: myHTTPD: 1.0\n";
    response->content_type = "Content -type: text/html\n\n";
    response->body = "<h1>MyHTTPd</h1\n";
    char *buftemp = fillBufferWithStruct(response);
    printf("Code HTTP: %s\n", response->http_code);
    printf("Code FILE : %s\n", response->http_message);
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