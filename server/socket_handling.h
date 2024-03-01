#ifndef SOCKET_HANDLING_H
#define SOCKET_HANDLING_H

#include "header.h"

int basic_socket_setup(int *sockfd, struct addrinfo **clients);

int socket_start(int *sockfd, struct addrinfo **clients);

#endif
