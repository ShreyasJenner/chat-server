/* Server Program */

#include "header.h"
#include "socket.h"

int main() {
    struct addrinfo *server, *client;
    int sockfd;

    /* Servers data */
    get_host_data(&server,"localhost","1234");
    /* Servers data */
    

    /* Client data */
    //get_host_data(&client,"localhost","4321");
    /* Client data */

    // Print IP address 
    printf("Server Starting\n");
    print_ip(server);

   
    sockfd = create_socket(server);
    while(1) {
        recv_msg(server, sockfd);
        //send_msg(client);
    }

    close(sockfd);
    freeaddrinfo(server);
    //freeaddrinfo(client);
    return 0;
}
