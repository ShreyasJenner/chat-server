#include "header.h"
#include "socket.h"

/* Error handling Function */
void error_handle(int code, char *str) {
    if(code<0) {
        perror(str);
        exit(1);
    }
}


/* Get host data and store in struct
 * Use HOST and PORT macros defined in header
 */
void get_host_data(struct addrinfo **server,char *host,char *port) {
    struct addrinfo test;
    int ret_code;

    /* Get HOST data and store in struct */
    memset(&test, 0, sizeof(test));
    test.ai_family = AF_INET;
    test.ai_socktype = SOCK_STREAM;
    test.ai_flags = AI_PASSIVE;
    /* Get HOST data and store in struct */

    ret_code = getaddrinfo(host, port, &test, server);
    error_handle(ret_code, "get address");
}


/* Function to print ip address of given system */
/* MODIFY THIS FUNCTION FOR GETTING PORT DYNAMICALLY*/
void print_ip(struct addrinfo *server) {
    struct addrinfo *p;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;
    in_port_t port_net_byte;

    void *addr;
    char *ipver;
    int port;

    char ipstr[INET6_ADDRSTRLEN];
    for(p=server; p != NULL; p = p->ai_next) {
        if(p->ai_family == AF_INET) {
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            port_net_byte = ipv4->sin_port;
            ipver = "IPv4";
        } else {
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            port_net_byte = ipv6->sin6_port;
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        port = ntohs(port_net_byte);
        
        printf("%s %s:%d\n",ipver,ipstr,port);
    }
}


/* Function to create and return socket */
int create_socket(struct addrinfo *server) {
    int sockfd, ret_code, yes;

    yes = 1;

    /* Create Socket */
    sockfd = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
    error_handle(sockfd, "Creating Socket");
    /* Create Socket */

    /* Set Socket Options */
    ret_code = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    error_handle(ret_code, "Set sock opt");
    /* Set Socket Options */

    /* Bind Socket */
    ret_code = bind(sockfd, server->ai_addr, server->ai_addrlen);
    error_handle(ret_code, "Binding socket");
    /* Bind Socket */

    /* Listen */
    listen(sockfd,1); //no of connection allowed passed as 2nd arg
    
    return sockfd;
}


/* Function to receive messages 
 * Accepts addrinfo struct and socket file descriptor as args
 */
void recv_msg(struct addrinfo *server, int sockfd) {
    struct sockaddr_storage conn;
    int bytes, conn_size, new_fd;

    char msg[MSG_SIZE];

    /* Accept Connection */
    conn_size = sizeof(conn);
    new_fd = accept(sockfd, (struct sockaddr *)&conn, &(conn_size));
    error_handle(new_fd, "Accepting Connection");
    /* Accept Connection */

    /* Receive Message */
    bytes = recv(new_fd, msg, sizeof(msg), 0);
    error_handle(bytes, "Receiving Data");
    close(new_fd);
    /* Receive Message */


    //printf("%sBytes Received:%d\n",msg,bytes);
    msg[strlen(msg)-1] = '\0';
    printf("[%d]%s\n",bytes,msg);

    /* Client closed connection */
    if(!strcmp(msg,"stop")) {
        exit(0);
    }
    /* Client closed connection */

    /* Clear Buffer */
    memset(msg, 0, MSG_SIZE);
    /* Clear Buffer */
}


/* Function to send messages */
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

