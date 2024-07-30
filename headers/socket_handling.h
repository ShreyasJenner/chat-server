#ifndef SOCKET_HANDLING_H
#define SOCKET_HANDLING_H

#include "header.h"

int basic_socket_setup(int *sockfd, struct addrinfo **clients);

int socket_start(int *sockfd, struct addrinfo **clients);

int accept_sockets(int sockfd, struct pollfd *pfds, int index);

void broadcast_msg(struct pollfd *pfds, char *buff, int active_clients, int curr_client);

#endif
