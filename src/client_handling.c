/*
 * Program deals with all functions related to clients in the chat server 
 * Implements the following functions:
 * display_client_req_info(clients: struct addrinfo *[]) -> void
 * get_host_ip(fd: int, host_ip: char*) -> int
 * get_host_port(host_port: char*) -> void
 * get_address_info(clients: struct addrinfo**, client_ip: char*, client_port: char*) -> void
 */

#include "client_handling.h"

/* Functions */

/* Function to display requested client socket information */
void display_client_req_info(struct addrinfo **clients, int size) {

    /* Variable Declaration */
    char ipstring[IP_WIDTH];        /* Store ip value */
    int i;
    struct addrinfo *ad_it;         /* iterator */ 

    /* Initialization */
    i = 0;

    for(ad_it = *clients; ad_it != NULL; ad_it = ad_it->ai_next) {
        if(ad_it->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)ad_it->ai_addr;
            struct in_addr *addr = &(ipv4->sin_addr);
            in_port_t *port = &(ipv4->sin_port);

            inet_ntop(ad_it->ai_family, addr, ipstring, sizeof(ipstring));
        }
    }
}


/* Function reads list of client ip addresses and ports from a file and stores into a character array 
 * used by get_address_info function to get client addressing info
 */
int get_host_ip(char *client_ip) {

    /* variables */
    struct ifreq ifr;       /* store ip details */
    int fd;                 /* file descriptor */
    
    /* open ip4 socket */
    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* set ifr address family as ip4 */
    ifr.ifr_addr.sa_family = AF_INET;

    /* copy wlo1 part from address */
    strncpy(ifr.ifr_name, "wlo1", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);

    /* Close file descriptor after use */
    close(fd);

    /* copy given ip4 address into client_ip */
    strcpy(client_ip, inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) );


    /* return 0 to indicate success */
    return 0;
}

void get_host_port(char *client_port) {
    /* set seed for random */
    srand(time(NULL));

    /* copy random generated port value into client_port */
    //sprintf(client_port, "%d", rand()%(UPPER_PORT-LOWER_PORT+1)+LOWER_PORT);

    strcpy(client_port,"1234");
}


/* Function gets client address info and stores into struct
 * It should be called after read_client_list function is called
 */
int get_address_info(struct addrinfo **client, char *client_ip, char *client_port) {
    
    struct addrinfo reference;

    memset(&reference, 0, sizeof(reference));                 
    
    // Allow IPv4 addresses
    reference.ai_family = AF_INET;                           
    // Set socket type
    reference.ai_socktype = SOCK_STREAM;                     
    // Fill in with IPv4 address suitable for bind and connect functions
    reference.ai_flags = AI_PASSIVE;                         
    
    // Store a linked list of structs into client
    if(getaddrinfo(client_ip, client_port, &reference, client)!=0) {
        return -1;
    }
    return 0;
}
