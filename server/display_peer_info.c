#include "display_peer_info.h"

/* Display Peer information as ip address and port */
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
