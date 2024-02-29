/* Header Files */
#include "header.h"
#include "read_peer_list.h"
#include "get_address_info.h"
#include "display_peer_info.h"

int main() {
    /* variables */    
    int fd;                                         /* file descriptor */
    int bytes_read;                                 /* store bytes read */
    int i, j;                                       /* Iterators */
    int flag;                                       /* Flag */
    char buff[BUF_SIZE];                            /* buffer */
    char peer_ip[PEER_NO][IP_WIDTH];                /* store peer ip addresses */
    char peer_port[PEER_NO][PORT_WIDTH];            /* store 4 digit peer ports */
    
    struct addrinfo *peers[PEER_NO];                              /* array of struct addrinfo */
    struct addrinfo *ad_it;                             /* iterator through addrinfo structure */


    /* Initialize variables */
    bytes_read = -1;
    // make all pointers point to NULL
    for(i=0;i<PEER_NO;i++)
        peers[i] = NULL;


    /* Open peer list file */
    if((fd = open("peer_list",O_RDONLY,0))<0) {
        perror("Opening peer list file");
        exit(1);
    }
    
    /* store peer list into peer_ip and peer_port */
    read_peer_list(fd, peer_ip, peer_port);


    /* Store the peer information into structs */
    get_address_info(&peers[0], peer_ip[0], peer_port[0]);
    get_address_info(&peers[1], peer_ip[1], peer_port[1]);

    

    /* Display peer information */
    display_peer_info(peers); 
     

    /* Close file descriptors */
    for(i=0;i<2;i++) {
        freeaddrinfo(peers[i]);
    }
    close(fd);

    return 0;
}
