#include "socket_handling.h"

/*
 * program handles socket creation, listening, accepting connections and receiving and sending messages using the sockets
 *
 * Functions:
 * basic_socket_setup(sockfd: int*, clients: struct addrinfo**) -> int
 * socket_start(sockfd: int*, clients: struct addrinfo**) -> int
 * accept_sockets(sockfd: int, pfds: struct pollfd*) -> int
 */


/* function handles basic socket setups including:
 * creation of socket for active clients
 * setting socket option for reuse of socket
 * returns number of active clients
 */
int basic_socket_setup(int *sockfd, struct addrinfo **clients) {
    
    /* Declaration */
    int i;                                                      /* Iterator */
    int yes;                                                    /* used to store 1 for setsockopt function */

    /*
     * For loop that iterates through all active clients 
     * pointers of clients point to NULL if they are not pointing to an active client
     */
    for(i=0; clients[i]!=NULL; i++) {
        /* Create socket for Active Peers */
        if((sockfd[i] = socket(clients[0]->ai_family, clients[0]->ai_socktype, clients[0]->ai_protocol)) < 0) {
            return -1;
        }

        /* Enable reuse of socket */
        yes = 1;
        if(setsockopt(sockfd[i], SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) != 0) {
            return -1;
        }
    }
    return i;
}



/* function binds socket and starts listening on it */
int socket_start(int *sockfd, struct addrinfo **clients) {

    /* Declaration */
    int i;                                                      /* Iterator */
    int yes;                                                    /* used to store 1 for setsockopt function */

    /*
     * For loop that iterates through all active clients 
     * pointers of clients point to NULL if they are not pointing to an active client
     */
    for(i=0; clients[i]!=NULL; i++) {
        /* Bind requested sockets for active clients */
        if(bind(sockfd[i], clients[i]->ai_addr, clients[i]->ai_addrlen)!=0) {
            return -1;
        }


        /* Listen on sockets that are to be connected to active clients */
        if(listen(sockfd[i], MAX_CON)!=0) {
            return -1;
        }
    }
}


/* function stores listening sockets into array after calling accept on client requested sockets */
int accept_sockets(int sockfd, struct pollfd *pfds) {
    /* Declaration */
    int i;                                                              /* Iterator */
    int size;                                                           /* stores size of structures */
    char sock_info[BUF_SIZE];                                            /* stores socket information */
    //struct sockaddr_storage connecting_client[CLIENT_NO];               /* store information of connecting client */
    struct sockaddr_in connecting_client;
    
    /* Accept connection to socket */
    size = sizeof connecting_client;

    if((pfds[2].fd=accept(sockfd, (struct sockaddr *)&connecting_client, &size))<0) {
        return -1;
    }
    pfds[2].events = POLLIN;

    printf("Client %d:\n",i);
    inet_ntop(connecting_client.sin_family, &connecting_client.sin_addr, sock_info, sizeof(sock_info));
    printf("%s:%d\n",sock_info,ntohs(connecting_client.sin_port));

    return 0;
}
