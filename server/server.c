/* Header Files */
#include "header.h"
#include "client_handling.h"
#include "error_handle.h"
#include "socket_handling.h"
#include "message.h"


int main() {
    /* variables */    
    int sockfd[FD_NO];                                              /* socket descriptor array */
    int listen_sockfd[FD_NO];                                           /* array for socket descriptors created when listening */
    int bytes_read;                                                 /* store bytes read */
    int i, j;                                                       /* Iterators */
    int active_clients;                                             /* Stores number of active clients for a session */
    int size;                                                       /* stores size of structures */
    int flag;                                                       /* Flag */
    char buff[BUF_SIZE];                                            /* buffer */
    char client_ip[CLIENT_NO][IP_WIDTH];                              /* store client ip addresses */
    char client_port[CLIENT_NO][PORT_WIDTH];                          /* store 4 digit client ports */
    
    struct addrinfo *clients[CLIENT_NO+1];                            /* null terminated array of pointers to struct addrinfo */
    struct sockaddr_storage connecting_client[CLIENT_NO];             /* store information of connecting client */
    

    /* Initialize variables */
    bytes_read = -1;
    // make all pointers point to NULL
    for(i=0;i<CLIENT_NO+1;i++)
        clients[i] = NULL;
    memset(sockfd, 0, sizeof(sockfd));
    memset(listen_sockfd, 0, sizeof(listen_sockfd));


    /* store client list into client_ip and client_port */
    /* Message */
    message("Reading client ip address and port");
    if(read_client_list(client_ip, client_port)!=0) {
        error_handle("Reading client list");
    }


    /* Store the client information into structs */
    /* Message */
    message("Storing client address information");
    if(get_address_info(&clients[0], client_ip[0], client_port[0])!=0)
        error_handle("getting address info for client");


    if(get_address_info(&clients[1], client_ip[1], client_port[1])!=0)
        error_handle("getting address info for client");

    

    /* Display client information */
    /* Message */
    message("Displaying Client Info");
    display_client_info(clients,CLIENT_NO); 
     
    
    /* setup sockets for all active clients */ 
    /* Message */
    message("Creating sockets for clients");
    if((active_clients=basic_socket_setup(sockfd, (struct addrinfo **)&clients))<0) {
        close_fd(sockfd);
        error_handle("Creating socket/Setting reuse of socket");
    }

    
    /* Start sockets by binding and listening */
    /* Message */
    message("Starting Sockets for sending/receiving messages");
    if(socket_start(sockfd, (struct addrinfo **)&clients)<0) {
        close_fd(sockfd);
        error_handle("Binding Sockets/Listening on Socket");
    }



    /* Accept connection to socket */
    size = sizeof connecting_client[0];
    if((listen_sockfd[0]=accept(sockfd[0], (struct sockaddr *)&connecting_client[0], &size))<0) {
        close_fd(sockfd);
        error_handle("accepting connection to socket");
    }

    /* receive message from socket */
    recv(listen_sockfd[0], buff, sizeof(buff), 0);
    printf("%s",buff);



    
    /* Free Memory allocated for struct addrinfo */
    /* Message */
    message("Freeing addrinfo structs containing client info");
    for(i=0;i<active_clients;i++) {
        freeaddrinfo(clients[i]);
    }

    /* Close descriptors in listening socket descriptor array */
    /* Message */
    message("Closing Listening Socket Descriptors");
    close_fd(listen_sockfd);
    /* Close descriptors in socket descriptor array */
    /* Message */
    message("Closing Socket Descriptors");
    close_fd(sockfd);

    return 0;
}
