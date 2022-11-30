#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#ifndef SERVER_H
#define SERVER_H

void Initsock(int *server_fd, int PORT, struct sockaddr_in *addres);
void Accept(int *new_socket, int *server_fd, struct sockaddr_in *address, int addrlen);

#endif
