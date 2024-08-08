/* Header Files */
#include "../headers/header.h"

void *read_stdin(void *sockfd) {
    char msg[100];
    int i;
    
    i = 0;
    // stop\n should be sent before loop ends
    while(strcmp(msg, "stop\n")) {
        // read a character from stdin
        msg[i++] = getchar();
        
        // if \n is entered then end the string with \0
        if(msg[i-1]=='\n') {
            msg[i] = '\0';
            i = 0;
        } else {    // otherwise continue to start of loop
            continue;
        }
        
        // send the msg with the \0 character [strlen + 1]
        if(send(*((int *)sockfd), msg, strlen(msg)+1, 0)<0) {
            perror("Sending data");
            exit(1);
        }
    }
    
    // close socket
    close(*(int *)sockfd);
    // exit program as client has signalled stop
    exit(1);
}

int main(int argc, char **argv) {

    /* variables */
    pthread_t thread;
    struct addrinfo server, *server_det;
    int sockfd, bytes_sent,i, bytes_recvd;
    char msg[100],ch;

    
    // if number of args <= 2 then exit pgm
    if(argc <= 2) {
        printf("Arguments missing\n");
        exit(1);
    }
    
    // prepare struct addrinfo 
    memset(&server, 0, sizeof server);
    server.ai_family = AF_INET;
    server.ai_socktype = SOCK_STREAM;
    server.ai_flags = AI_PASSIVE;
    
    // get address info and store in server struct
    if(getaddrinfo(argv[1], argv[2], &server, &server_det)<0) {
        perror("getting address info");
        exit(1);
    }
    
    // create a socket for client connection to server 
    if((sockfd = socket(server_det->ai_family, server_det->ai_socktype, server_det->ai_protocol))<0) {
        perror("creating socket");
        exit(1);
    }
    
    // connect to server
    if(connect(sockfd, server_det->ai_addr, server_det->ai_addrlen)<0) {
        perror("connecting to socket");
        exit(1);
    }
    
    // set socket to nonblocking
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // Create Thread
    pthread_create(&thread, NULL, read_stdin, &sockfd);
    
    // infinite loop to receive messages from socket 
    // thread handles sending messages to server
    while(1) {
        // if server closes connection then break out of loop
        if((bytes_recvd=recv(sockfd, msg, sizeof(msg), 0))==0) {
            break;
        } else if(bytes_recvd>0) {
            msg[bytes_recvd] = '\0';
            printf("%s",msg);
        }
    }
        
    // close the socket
    close(sockfd);

    return 0;
}
