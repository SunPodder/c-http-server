#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <time.h>
#include <unistd.h>
#include <bits/seek_constants.h>
#include <string.h>
#include "response.h"


char *responseServerName = "Server: C HTTP Server/1.0\n\r";

void getResponseTime(char* responseDate){
    time_t date;
    time(&date);
    sprintf(responseDate, "Date: %s", ctime(&date));
}

void HTTPResponse(int socket, char *mimeType, int fd){
    char *responseDate = (char*)malloc(100);
    getResponseTime(responseDate);

    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char *contentLength = (char*)malloc(100);
    sprintf(contentLength, "Content-Length: %d\n\r", size);

    char *contentType = (char*)malloc(100);
    sprintf(contentType, "Content-Type: %s\n\r", mimeType);

    send(socket, responseServerName, strlen(responseServerName), 0);
    send(socket, responseDate, strlen(responseDate), 0);
    send(socket, contentLength, strlen(contentLength), 0);
    send(socket, contentType, strlen(contentType), 0);
    send(socket, "\n", 1, 0);
    sendfile(socket, fd, 0, size);

    // free memory
    free(responseDate);
    free(contentLength);
    free(contentType);
    close(fd);
}


void HTTPRaw(int socket, char* mimeType,char* response){
    char *responseDate = (char*)malloc(100);
    getResponseTime(responseDate);

    char *contentLength = (char*)malloc(100);
    sprintf(contentLength, "Content-Length: %lu\n\r", strlen(response));

    char *contentType = (char*)malloc(100);
    sprintf(contentType, "Content-Type: %s\n\r", mimeType);

    
    send(socket, responseServerName, strlen(responseServerName), 0);
    send(socket, responseDate, strlen(responseDate), 0);
    send(socket, contentLength, strlen(contentLength), 0);
    send(socket, contentType, strlen(contentType), 0);
    send(socket, "\n", 1, 0);
    send(socket, response, strlen(response), 0);
}
