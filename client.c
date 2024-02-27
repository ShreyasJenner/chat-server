/* Client Program */

#include "header.h"
#include "socket.h"

int main() {
    struct addrinfo *server, *client;
    int sockfd;
    char msg[MSG_SIZE], path[MSG_SIZE], file[MSG_SIZE];

    /* Servers data */
    get_host_data(&server,"localhost","1234");
    /* Servers data */

    /* Client data */
    //get_host_data(&client, "localhost", "4321");
    /* Client data */

    // Print Ip address
    printf("Client Starting\n");
    //print_ip(client);


    //sockfd = create_socket(client);
    
    memset(msg,0,MSG_SIZE);
    gethostname(msg, MSG_SIZE);
    send_msg(server, msg);
    while(1) {
        /* Clear Buffer */
        memset(msg, 0, MSG_SIZE);
        /* Clear Buffer */
        
        fgets(msg, MSG_SIZE, stdin);
        send_msg(server,msg); 
    }

    close(sockfd);
    //freeaddrinfo(client);
    freeaddrinfo(server);

    return 0;
}
