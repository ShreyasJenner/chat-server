#ifndef HEADER_H
#define HEADER_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>


#define BUF_SIZE 100            /* size of string buffer */
#define PEER_NO 10              /* max number of peers */
#define IP_WIDTH 16             /* width of ip addr string */
#define PORT_WIDTH 5            /* width of port string */
#define FD_NO PEER_NO+1         /* max number of file descriptors */

#endif
