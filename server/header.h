#ifndef HEADER_H
#define HEADER_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <net/if.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define BUF_SIZE 100                /* size of string buffer */
#define CLIENT_NO 10                /* max number of clients */
#define IP_WIDTH 17                 /* width of ip addr string */
#define PORT_WIDTH 7                /* width of port string */
#define UPPER_PORT 30000            /* upper port limit */
#define LOWER_PORT 20000            /* lower port limit */
#define FD_NO CLIENT_NO+1           /* max number of file descriptors */
#define MAX_CON 10                  /* max allowed connections on port*/

#endif
