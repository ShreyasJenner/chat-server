/* Header Files */
#include "header.h"
#include "peer_handling.h"
#include "error_handle.h"


int main() {
    /* variables */    
    int fd[FD_NO];                                              /* file descriptor array */
    int bytes_read;                                             /* store bytes read */
    int i, j;                                                   /* Iterators */
    int flag;                                                   /* Flag */
    char buff[BUF_SIZE];                                        /* buffer */
    char peer_ip[PEER_NO][IP_WIDTH];                            /* store peer ip addresses */
    char peer_port[PEER_NO][PORT_WIDTH];                        /* store 4 digit peer ports */
    
    struct addrinfo *peers[PEER_NO];                            /* array of pointers to struct addrinfo */
    

    /* Initialize variables */
    bytes_read = -1;
    // make all pointers point to NULL
    for(i=0;i<PEER_NO;i++)
        peers[i] = NULL;


    /* Open peer list file */
    if((fd[0] = open("peer_list",O_RDONLY,0))<0) {
        close_fd(fd,FD_NO);
        error_handle("Opening peer list file");
    }
    
    /* store peer list into peer_ip and peer_port */
    read_peer_list(fd[0], peer_ip, peer_port);


    /* Store the peer information into structs */
    get_address_info(&peers[0], peer_ip[0], peer_port[0]);
    get_address_info(&peers[1], peer_ip[1], peer_port[1]);

    

    /* Display peer information */
    display_peer_info(peers); 
     
    
    /* Create socket to Peer */
    if((fd[1] = socket(peers[0]->ai_family, peers[0]->ai_socktype, peers[0]->ai_protocol)) < 0) {
        close_fd(fd, FD_NO);
        error_handle("Creating socket");
    }

    /* Bind socket */

    
    /* Free Memory allocated for struct addrinfo */
    /* INCOMPLETE */
    /* CHANGE TO HANDLE DYNAMIC NUMBER OF ACTIVE PEERS */
    for(i=0;i<2;i++) {
        freeaddrinfo(peers[i]);
    }

    /* Close file descriptors in file descriptor array */
    close_fd(fd,FD_NO);

    return 0;
}
