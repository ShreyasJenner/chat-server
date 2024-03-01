/*
 * Program deals with all functions related to peers in the chat server 
 * Implements the following functions:
 * display_peer_info(peers: struct addrinfo *[]) -> void
 * read_peer_list(fd: int, peer_ip: char[][], peer_port[][]) -> void
 * get_address_info(peers: struct addrinfo**, peer_ip: char*, peer_port: char*) -> void
 */

#include "peer_handling.h"

/* Functions */

/* Function to display Peer information as ip address and port */
void display_peer_info(struct addrinfo *peers[PEER_NO]) {
    /* Message */
    printf("Displaying Peer Info\n");

    /* Variable Declaration */
    char ipstring[IP_WIDTH];        /* Store ip value */
    int i;
    struct addrinfo *ad_it;         /* iterator */ 

    /* Initialization */
    i = 0;

    /* Iterate thorugh array of pointers of struct addrinfo */
    while(i<PEER_NO && peers[i]!=NULL) {
        for(ad_it = peers[i]; ad_it != NULL; ad_it = ad_it->ai_next) {
            if(ad_it->ai_family == AF_INET) {
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)ad_it->ai_addr;
                struct in_addr *addr = &(ipv4->sin_addr);
                in_port_t *port = &(ipv4->sin_port);

                inet_ntop(ad_it->ai_family, addr, ipstring, sizeof(ipstring));
                printf("%s:%d\n",ipstring,ntohs(*port));
            }
        }
        i++;
    }
}


/* Function reads list of peer ip addresses and ports from a file and stores into a character array 
 * used by get_address_info function to get peer addressing info
 */
void read_peer_list(int fd, char peer_ip[PEER_NO][IP_WIDTH], char peer_port[PEER_NO][PORT_WIDTH]) {
    /* Message */
    printf("Reading Peer list into peer_ip and peer_port\n");

    /* variables */
    int i,j,flag, bytes_read;
    char buff[1]; // store character read from file
    
    /* store bytes read */
    bytes_read = -1;

    /* Iterators */
    i = 0;
    j = 0;

    /* Flags */
    flag = 0;

    /* 
     * Loop reads 1 character from peer list file till EOF
     * Stores the character into peer_ip or peer_port
     */
    while((bytes_read = read(fd, buff, 1)) != 0) {
        /* Error handling */
        if(bytes_read==-1) {
            perror("Reading peer list file");
            exit(1);
        }
        
        if(flag) {
            if(buff[0] == '\n') {
                peer_port[i][j] = '\0';
                i++;
                j = 0;
                flag = 0;
            } else {
                peer_port[i][j++] = buff[0];
            }
        } else {
            if(buff[0] == ' ') {
                peer_ip[i][j] = '\0';
                j = 0;
                flag = 1;
            } else {
                peer_ip[i][j++] = buff[0];
            }
        }
    }
}


/* Function gets peer address info and stores into struct
 * should be called after read_peer_list function is called
 */
void get_address_info(struct addrinfo **peer, char *peer_ip, char *peer_port) {
    /* Message */
    printf("Getting Peer Address Info\n");
    
    struct addrinfo reference;

    memset(&reference, 0, sizeof(reference));                 
    
    // Allow IPv4 addresses
    reference.ai_family = AF_INET;                           
    // Set socket type
    reference.ai_socktype = SOCK_STREAM;                     
    // Fill in with IPv4 address suitable for bind and connect functions
    reference.ai_flags = AI_PASSIVE;                         
    
    // Return a linked list of structs to peer
    if(getaddrinfo(peer_ip, peer_port, &reference, peer)!=0) {
        perror("gettingaddrinfo for peer");
        exit(1);
    }
}
