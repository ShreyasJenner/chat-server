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
    int flag;                                                       /* Flag */
    char buff[BUF_SIZE];                                            /* buffer */
    char client_ip[CLIENT_NO][IP_WIDTH];                              /* store client ip addresses */
    char client_port[CLIENT_NO][PORT_WIDTH];                          /* store 4 digit client ports */
    
    struct addrinfo *clients[CLIENT_NO+1];                            /* null terminated array of pointers to struct addrinfo */
    

    /* Initialize variables */
    bytes_read = -1;
    // make all pointers point to NULL
    for(i=0;i<CLIENT_NO+1;i++)
        clients[i] = NULL;
    memset(sockfd, 0, sizeof(sockfd));
    memset(listen_sockfd, 0, sizeof(listen_sockfd));


    /* store client list into client_ip and client_port */
    /* Message */
    message("READING CLIENT IP ADDRESS AND PORT");
    if(read_client_list(client_ip, client_port)!=0) {
        error_handle("Reading client list");
    }


    /* Store the client information into structs */
    /* Message */
    message("STORING REQUESTED SOCKET INFORMATION");
    if(get_address_info(&clients[0], client_ip[0], client_port[0])!=0)
        error_handle("getting address info for requested socket");


    if(get_address_info(&clients[1], client_ip[1], client_port[1])!=0)
        error_handle("getting address info for requested socket");

    

    /* Display active requested sockets */
    /* Message */
    message("DISPLAYING REQUESTED SOCKETS INFO");
    display_client_req_info(clients,CLIENT_NO); 
     
    
    /* setup sockets for all active clients */ 
    /* Message */
    message("CREATING SOCKETS FOR CLIENTS");
    if((active_clients=basic_socket_setup(sockfd, (struct addrinfo **)&clients))<0) {
        close_fd(sockfd);
        error_handle("Creating socket/Setting reuse of socket");
    }

    
    /* Start sockets by binding and listening */
    /* Message */
    message("STARTING SOCKETS FOR SENDING/RECEIVING MESSAGES");
    if(socket_start(sockfd, (struct addrinfo **)&clients)<0) {
        close_fd(sockfd);
        error_handle("Binding Sockets/Listening on Socket");
    }


    /* Get sockets for listening to clients */
    /* Message */
    message("STARTING LISTENING SOCKETS");
    struct pollfd pfds[CLIENT_NO];
    pfds[0].fd = sockfd[0];
    pfds[0].events = POLLIN;
    pfds[1].fd = sockfd[1];
    pfds[1].events = POLLIN;
    int bytes_recv;

    int temp; //temp var
          
    while(1) {
        buff[0] = '\0';

        if(pfds[0].revents & POLLIN)
            accept_sockets(sockfd[0],pfds);

        if(pfds[1].revents & POLLIN)
            accept_sockets(sockfd[1],pfds);

        bytes_recv = recv(pfds[2].fd, buff, sizeof(buff), 0);
        if(bytes_recv==0) {
            printf("CLIENT %d DISCONNECTED\n",pfds[2].fd);
            break;
        }
        else if(bytes_recv!=-1) {
            buff[bytes_recv-1] = '\0';
            printf("%d[%d]:%s\n",pfds[2].fd,bytes_recv,buff);
        }

        if(!strcmp(buff,"stop"))
            break;
    }
    

    
    /* Free Memory allocated for struct addrinfo */
    /* Message */
    message("FREEING ADDRINFO STRUCTS CONTAINING SOCKET INFO");
    for(i=0;i<active_clients;i++) {
        freeaddrinfo(clients[i]);
    }

    /* Close descriptors in listening socket descriptor array */
    /* Message */
    message("CLOSING LISTENING SOCKET DESCRIPTORS");
    close_fd(listen_sockfd);
    /* Close descriptors in socket descriptor array */
    /* Message */
    message("CLOSING SOCKET DESCRIPTORS");
    close_fd(sockfd);

    return 0;
}
