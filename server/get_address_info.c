#include "get_address_info.h"

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
