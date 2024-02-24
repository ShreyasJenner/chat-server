/* Client Program */

#include "header.h"

void error_handle(int code, char *str) {
    if(code<0) {
        perror(str);
        exit(1);
    }
}

void print_ip(struct addrinfo *server) {
    struct addrinfo *p;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;

    void *addr;
    char *ipver;

    char ipstr[INET6_ADDRSTRLEN];
    for(p=server; p != NULL; p = p->ai_next) {
        if(p->ai_family == AF_INET) {
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        
        printf("%s: %s\n",ipver,ipstr);
    }
}

int main() {
    struct addrinfo *server, test;
    struct sockaddr_storage conn; 
    int ret_code, sockfd, yes, conn_size, new_fd, bytes;

    char msg[100];

    /* Initialize variables */
    ret_code = 1;

    /* Get HOST data and store in struct */
    memset(&test, 0, sizeof(test));
    test.ai_family = AF_INET;
    test.ai_socktype = SOCK_STREAM;
    test.ai_flags = AI_PASSIVE;

    ret_code = getaddrinfo(HOST, PORT, &test, &server);
    error_handle(ret_code,"get address");
   
    
    /* Create Socket */
    sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    error_handle(sockfd,"Creating Socket");

    
    /* Connect Socket */
    ret_code = connect(sockfd, server->ai_addr, server->ai_addrlen);
    error_handle(ret_code, "connecting to socket");


    /* Send Message */
    scanf("%[^\n]", msg);
    bytes = send(sockfd, msg, strlen(msg), 0);
    error_handle(bytes, "Sending Data");
    printf("Bytes Sent:%d\n",bytes);
    /* Send Message */

    close(sockfd);
    freeaddrinfo(server);

    return 0;
}
