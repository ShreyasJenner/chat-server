/* Header Files */
#include "header.h"
#include "client_handling.h"
#include "error_handle.h"
#include "socket_handling.h"
#include "message.h"


int main() {
    /* variables */    
    int bytes_recv;                                                 /* stores the number of bytes received when sending/receving */
    int disconnect_flag;                                            /* disconnect flag for main while loop */
    int sockfd;                                                     /* socket descriptor array */
    int listen_sockfd[FD_NO];                                       /* array for socket descriptors created when listening */
    int bytes_read;                                                 /* store bytes read */
    int i, j;                                                       /* Iterators */
    int active_clients;                                             /* Stores number of active clients for a session */
    int flag;                                                       /* Flag */
    char buff[BUF_SIZE];                                            /* buffer */
    char client_ip[IP_WIDTH];                            /* store client ip addresses */
    char client_port[PORT_WIDTH];                        /* store 4 digit client ports */
    char client_name[20];                                           /* client name storage */
    
    struct addrinfo *clients;                                       /* null terminated array of pointers to struct addrinfo */
    struct pollfd pfds[CLIENT_NO];                                  /* stores the pollfd struct for sockets that are polled to */
    

    /* Initialize variables */
    active_clients = 0;
    bytes_read = -1;
    disconnect_flag = 0;
    // make all pointers point to NULL
    clients = NULL;
    memset(listen_sockfd, 0, sizeof(listen_sockfd));


    /* store client list into client_ip and client_port */
    /* Log time into file */
    time_message();
    message("READING CLIENT IP ADDRESS AND PORT");
    if(read_client_list(client_ip, client_port)!=0) {
        error_handle("Reading client list");
    }
    
    /* Print client ip and port */
    printf("Hosting: %s %s\n",client_ip,client_port);


    /* Store the client information into structs */
    /* Message */
    message("STORING REQUESTED SOCKET INFORMATION");
    if(get_address_info(&clients, client_ip, client_port)!=0) {
        error_handle("getting address info for socket");
    }

    

    /* Display active requested sockets */
    /* Message */
    message("DISPLAYING REQUESTED SOCKETS INFO");
    display_client_req_info(&clients,CLIENT_NO); 
     
    
    /* create sockets for all active clients */ 
    /* Message */
    message("CREATING SOCKETS FOR CLIENTS");
    if((active_clients=basic_socket_setup(&sockfd, (struct addrinfo **)&clients))<0) {
        close_fd(&sockfd);
        error_handle("Creating socket/Setting reuse of socket");
    }

    
    /* Start sockets by binding and listening */
    /* Message */
    message("STARTING SOCKETS FOR SENDING/RECEIVING MESSAGES");
    if(socket_start(&sockfd, (struct addrinfo **)&clients)<0) {
        close_fd(&sockfd);
        error_handle("Binding Sockets/Listening on Socket");
    }


    /* Get sockets for listening to clients */
    /* Message */
    message("STARTING LISTENING SOCKETS");

   
    /* set socket to nonblocking */
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    /* poll pre-determined number of sockets in pfds array */
    while(poll(pfds,active_clients,1000)!=-1 && !disconnect_flag) {
        buff[0] = '\0';

        /* accept socket otherwise continue */
        if(accept_sockets(sockfd, pfds, active_clients)==0)
            active_clients++;
        
        /* loop through pfds array checking for sockets that have data in them */
        for(i=0;i<active_clients;i++) {
            if(pfds[i].revents & POLLIN) {
                bytes_recv = recv(pfds[i].fd, buff, sizeof(buff), 0);
                if(bytes_recv==0) { /* client has disconnected */
                    disconnect_flag = 1;
                    
                    /* put the message into buff and log it */
                    sprintf(buff, "CLIENT %d DISCONNECTED\n",pfds[i].fd);
                    message(buff);

                    /* Copy `disconnect msg` to buffer client */
                    strcpy(buff,"Other Client disconnected\n");

                    /* send msg to other clients through socket */
                    for(j=0;j<active_clients;j++) {
                        /* if disconnecting socket is not being pointed to by j */
                        if(j!=i)
                            send(pfds[j].fd, buff, strlen(buff), 0);
                    }
                    break;
                }
                /* else if there is no error in reading socket */
                else if(bytes_recv>0) {
                    /* close string received with \n\0 */
                    buff[bytes_recv-1] = '\n';
                    buff[bytes_recv] = '\0';

                    /* print on stdout without \n as it already has \n */
                    printf("%d[%d]:%s",pfds[i].fd,bytes_recv,buff);

                    /* store client details in variable client_name */ 
                    strcpy(client_name,"Client ");
                    snprintf(client_name, 10, "%d :", i);

                    /* send client details to all other clients */
                    for(j=0;j<active_clients;j++) {
                        if(j!=i) {
                            send(pfds[j].fd, client_name, strlen(client_name), 0);
                            /* send msg to other clients socket */
                            send(pfds[j].fd, buff, strlen(buff), 0);
                        }
                    }
                }
            }

        }
    }
    

    
    /* Free Memory allocated for struct addrinfo */
    /* Message */
    message("FREEING ADDRINFO STRUCTS CONTAINING SOCKET INFO");
    freeaddrinfo(clients);

    /* Close descriptors in listening socket descriptor array */
    /* Message */
    message("CLOSING LISTENING SOCKET DESCRIPTORS");
    close_fd(listen_sockfd);
    /* Close descriptors in socket descriptor array */
    /* Message */
    message("CLOSING SOCKET DESCRIPTORS");
    close_fd(&sockfd);

    return 0;
}
