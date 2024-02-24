/* Client Program */

#include "header.h"

void error_handle(int code, char *str) {
    if(code<0) {
        perror(str);
        exit(1);
    }
}

void send_msg(struct addrinfo *server) {
    int sockfd, ret_code, bytes_sent;
    char msg[MSG_SIZE];

    /* Create Socket */
    sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    error_handle(sockfd, "Creating Socket");
    /* Create Socket */

    /* Connect Socket */
    ret_code = connect(sockfd, server->ai_addr, server->ai_addrlen);
    error_handle(ret_code, "connecting to socket");
    /* Connect Socket */

    /* Clear Buffer */
    memset(msg, 0, MSG_SIZE);
    /* Clear Buffer */

    /* Send Message */
    fgets(msg,MSG_SIZE,stdin);
    bytes_sent = send(sockfd, msg, strlen(msg), 0);
    error_handle(bytes_sent, "Sending message");
    printf("Bytes sent:%d\n",bytes_sent);
    /* Send Message */

    close(sockfd);

    /* Client wants to close */
    msg[strlen(msg)-1] = '\0';
    if(!strcmp(msg,"stop")) {
        exit(0);
    }
    /* Client wants to close */
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

    while(1) {
        send_msg(server); 
    }

    freeaddrinfo(server);

    return 0;
}
