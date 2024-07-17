/*
 * Program deals with all functions related to clients in the chat server 
 * Implements the following functions:
 * display_client_req_info(clients: struct addrinfo *[]) -> void
 * read_client_list(fd: int, client_ip: char[][], client_port[][]) -> void
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

    /* Iterate thorugh array of pointers of struct addrinfo */
    /*
    while(i<size && clients[i]!=NULL) {
        for(ad_it = clients[i]; ad_it != NULL; ad_it = ad_it->ai_next) {
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
    */
        for(ad_it = *clients; ad_it != NULL; ad_it = ad_it->ai_next) {
            if(ad_it->ai_family == AF_INET) {
                struct sockaddr_in *ipv4 = (struct sockaddr_in *)ad_it->ai_addr;
                struct in_addr *addr = &(ipv4->sin_addr);
                in_port_t *port = &(ipv4->sin_port);

                inet_ntop(ad_it->ai_family, addr, ipstring, sizeof(ipstring));
                printf("%s:%d\n",ipstring,ntohs(*port));
            }
        }
}


/* Function reads list of client ip addresses and ports from a file and stores into a character array 
 * used by get_address_info function to get client addressing info
 */
int read_client_list(char client_ip[CLIENT_NO][IP_WIDTH], char client_port[CLIENT_NO][PORT_WIDTH]) {

    /* variables */
    int i,j,flag, bytes_read;
    int fd;                 /* file descriptor */
    char buff[1];           /* store character read from file */
    
    /* store bytes read */
    bytes_read = -1;

    /* Iterators */
    i = 0;
    j = 0;

    /* Flags */
    flag = 0;

    
    /* Open client list file */
    if((fd = open("client_list",O_RDONLY,0))<0) {
        return -1;
    }


    /* 
     * Loop reads 1 character from client list file till EOF
     * Stores the character into client_ip or client_port
     */
    while((bytes_read = read(fd, buff, 1)) != 0) {
        /* Error handling */
        if(bytes_read==-1) {
            return -1;
        }
        
        if(flag) {
            if(buff[0] == '\n') {
                client_port[i][j] = '\0';
                i++;
                j = 0;
                flag = 0;
            } else {
                client_port[i][j++] = buff[0];
            }
        } else {
            if(buff[0] == ' ') {
                client_ip[i][j] = '\0';
                j = 0;
                flag = 1;
            } else {
                client_ip[i][j++] = buff[0];
            }
        }
    }
    
    /* Close file descriptor after use */
    close(fd);

    /* return 0 to indicate success */
    return 0;
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
