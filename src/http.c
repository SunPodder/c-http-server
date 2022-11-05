/*
 * Simple HTTP Server
 * Author:  Sun Podder
 * github:  https://github.com/SunPodder/c-http-server
 * License: GPL 2.0
 * Description:
 * A simple HTTP server written in C. It can serve static files from the current
 * directory
 */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <asm/fcntl.h>
#include <bits/in_addr.h>
#include "response.h"
#include "mime.h"
#include "utils.h"



int main(int argc, char *argv[]) {

  int PORT = 8080;
  char* HTTP404 = "HTTP/1.1 404 Not Found\n\r";
  char* HTTP200 = "HTTP/1.1 200 OK\n\r";
  
  if(argc > 1){
      PORT = atoi(argv[1]);
  }

  int server_fd, new_socket, valread;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[30000] = {0};

  // create a socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // attach socket to port 8080
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // bind the socket to PORT
  // if the bind fails, exit the program
  // if the bind succeeds, start listening for connections
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    char *e = malloc(100);
    sprintf(e, "Cannot bind to PORT %d", PORT);
    perror(e);
    free(e);
    exit(EXIT_FAILURE);
  }
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    printf("Cannot listen on PORT: %d\n", PORT);
    exit(EXIT_FAILURE);
  }

  printf("Listening on PORT: %d\n", PORT);

  // accept a connection
  // if the accept fails, log the error and continue listening for connections
  // if the accept succeeds, read the request and send a response
  // then close the connection and continue listening for connections
  while (1) {

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0) {
      perror("Error while receiving connection");
      continue;
    }

    valread = read(new_socket, buffer, 30000);

    // if the request is for a directory, serve index.html
    // if the request is for a file, serve the file
    // if none of them found, send 404
    char *req = strtok(buffer, " ");
    char *path = strtok(NULL, " ");
    char *file = malloc(sizeof(path) + 100);
    strcpy(file, path + 1);

    if(isFile(file) == 0 && !strEndsWith(path, "/")){
        strcat(path, "/");

        char* r = (char*)malloc(50 + strlen(path));
        sprintf(r, "HTTP/1.1 301 Moved Permanently\n\rLocation: %s\n\r", path);
        printf("%s\n", r);
        send(new_socket, r, 0, strlen(r));
        free(r);
        close(new_socket);
        continue;
    }

    if (strEndsWith(path, "/")) {
        sprintf(file, "%sindex.html", path + 1);
    }

    if (access(file, F_OK) != 0) {
      printf("GET %s - Not Found\n", path);

      // if index, send directory index
      // else send 404 only
      if (strcmp(path, "/") == 0) {
        //TODO: List the requested directory and send the index
        send(new_socket, HTTP404, strlen(HTTP404), 0);
        HTTPRaw(new_socket, "text/html","<h1>Index of dir:</h1>");
      } else {

        send(new_socket, HTTP404, strlen(HTTP404), 0);
        char* res = malloc(sizeof(path) + 50);
        sprintf(res,
                "<html>"
                "<head><title>Error 404: File not found</title></head>"
                "<body>"
                "<pre style='font-size: 400%%;'><code>%s</code></pre><h1>No such file or directory</h1>"
                "</body></html>",
                path);
        HTTPRaw(new_socket, "text/html", res);
        free(res);
      }

    } else {
      printf("GET %s\n", path);

      int fd = open(file, O_RDONLY);
      send(new_socket, HTTP200, strlen(HTTP200), 0);
      HTTPResponse(new_socket, getMimeType(file), fd);
    }

    free(file);
    close(new_socket);
  }
  return 0;
}
