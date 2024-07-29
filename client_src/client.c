/* Header Files */
#include "../src/header.h"
#include <sys/socket.h>

int main(int argc, char **argv) {

    /* variables */
    struct addrinfo server, *server_det;
    int sockfd, bytes_sent,i;
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
    
    while(1) {
        scanf("%[^\n]", msg);
        getchar();
        if(send(sockfd, msg, strlen(msg), 0)<0) {
            perror("Sending data");
            exit(1);
        }

        if(recv(sockfd, msg, sizeof(msg), 0)==0) {
            break;
        } else {
            printf("%s\n",msg);
        }
    }
        
    close(sockfd);

    return 0;
}
