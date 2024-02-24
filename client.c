/* Client Program */

#include "header.h"
#include "socket.h"

int main() {
    struct addrinfo *server, *client;
    int sockfd;

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
    while(1) {
        send_msg(server); 
        //recv_msg(client, sockfd);
    }

    close(sockfd);
    //freeaddrinfo(client);
    freeaddrinfo(server);

    return 0;
}
