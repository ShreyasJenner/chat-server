#include "../headers/socket_handling.h"

/*
 * program handles socket creation, listening, accepting connections and receiving and sending messages using the sockets
 *
 * Functions:
 * basic_socket_setup(sockfd: int*, clients: struct addrinfo**) -> int
 * socket_start(sockfd: int*, clients: struct addrinfo**) -> int
 * accept_sockets(sockfd: int, pfds: struct pollfd*, index: int) -> int
 * broadcast_msg(pfds: struct pollfd*, buff: char*, active_clients: int, curr_client: int) {
 */


/* function handles basic socket setups including:
 * creation of socket for active clients
 * setting socket option for reuse of socket
 * returns number of active clients or 0
 */
int basic_socket_setup(int *sockfd, struct addrinfo **clients) {
    
    /* Declaration */
    int i;                                                      /* Iterator */
    int yes;                                                    /* used to store 1 for setsockopt function */

    if((*sockfd = socket((*clients)->ai_family, (*clients)->ai_socktype, (*clients)->ai_protocol)) < 0) {
        return -1;
    }
    return 0;
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
    /*
    for(i=0; clients[i]!=NULL; i++) {
        // Bind requested sockets for active clients
        if(bind(sockfd[i], clients[i]->ai_addr, clients[i]->ai_addrlen)!=0) {
            return -1;
        }


        // Listen on sockets that are to be connected to active clients
        if(listen(sockfd[i], MAX_CON)!=0) {
            return -1;
        }
    }
    */

    if(bind(*sockfd, (*clients)->ai_addr, (*clients)->ai_addrlen) != 0) {
        return -1;
    }

    if(listen(*sockfd, MAX_CON)!=0) {
        return -1;
    }
}


/* 
 * Function stores listening sockets into array after calling accept on client requested sockets 
 * returns 0 on success
 * */
int accept_sockets(int sockfd, struct pollfd *pfds, int index) {
    int size;                                                               /* stores size of structures */
    char sock_info[BUF_SIZE], buff[BUF_SIZE];                               /* stores socket information */
    //struct sockaddr_storage connecting_client[CLIENT_NO];                 /* store information of connecting client */
    struct sockaddr_in connecting_client;
    
    /* Accept connection to socket */
    size = sizeof connecting_client;
    
    if((pfds[index].fd=accept(sockfd, (struct sockaddr *)&connecting_client, &size))<0) {
        return -1;
    }
    pfds[index].events = POLLIN;
    
    if(index == 0) {
        printf("Server has joined\n");
    } 
    else {
        inet_ntop(connecting_client.sin_family, &connecting_client.sin_addr, sock_info, sizeof(sock_info));
        sprintf(buff, "Client %s:%d joined\n",sock_info,ntohs(connecting_client.sin_port)); 
        broadcast_msg(pfds, buff, index, index);
    }

    return 0;
}


/* 
 * Function broadcasts messages to all connected clients
 */
void broadcast_msg(struct pollfd *pfds, char *buff, int active_clients, int curr_client) {
    /* Declaration */
    int j;
    
    /* Send message to all clients except curr one */
    for(j=0;j<active_clients;j++) {
        /* if disconnecting socket is not being pointed to by j */
        if(j!=curr_client)
            send(pfds[j].fd, buff, strlen(buff), 0);
    }
}
