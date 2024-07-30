/* Header Files */
#include "../headers/header.h"

void *read_stdin(void *sockfd) {
    char msg[100];
    int i;
    
    i = 0;
    while(strcmp(msg, "stop")) {
        msg[i++] = getchar();

        if(msg[i-1]=='\n') {
            msg[i] = '\0';
            i = 0;
        }

        if(send(*((int *)sockfd), msg, strlen(msg), 0)<0) {
            perror("Sending data");
            exit(1);
        }
    }

    return NULL;
}

int main(int argc, char **argv) {

    /* variables */
    pthread_t thread;
    struct addrinfo server, *server_det;
    int sockfd, bytes_sent,i, bytes_recvd;
    char msg[100],ch;


    if(argc <= 2) {
        printf("Arguments missing\n");
        exit(1);
    }

    memset(&server, 0, sizeof server);
    server.ai_family = AF_INET;
    server.ai_socktype = SOCK_STREAM;
    server.ai_flags = AI_PASSIVE;

    if(getaddrinfo(argv[1], argv[2], &server, &server_det)<0) {
        perror("getting address info");
        exit(1);
    }

    if((sockfd = socket(server_det->ai_family, server_det->ai_socktype, server_det->ai_protocol))<0) {
        perror("creating socket");
        exit(1);
    }

    if(connect(sockfd, server_det->ai_addr, server_det->ai_addrlen)<0) {
        perror("connecting to socket");
        exit(1);
    }

    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    // Create Thread
    pthread_create(&thread, NULL, read_stdin, &sockfd);
    
    while(1) {
        if((bytes_recvd=recv(sockfd, msg, sizeof(msg), 0))==0) {
            break;
        } else if(bytes_recvd>0) {
            msg[bytes_recvd] = '\0';
            printf("%s",msg);
        }
    }
        
    close(sockfd);

    return 0;
}
