#include "../headers/message_handling.h"

/*
 * broadcast_msg(pfds: struct pollfd*, buff: char*, active_clients: int, curr_client: int) -> void
 * send_msg(int sender_index, int receiver_index, struct pollfd *pfds, char *buff) -> void
*/


/* 
 * Function broadcasts messages to all connected clients
 */
void broadcast_msg(struct pollfd *pfds, char *buff, int active_clients, int curr_client) {
    // Declaration
    printf("Inside broadcast msg funct\n");
    int j;
    
    // Send message to all clients except curr one
    for(j=0;j<active_clients;j++) {
        // if disconnecting socket is not being pointed to by j and socket hasnt disconnected
        if(j!=curr_client && pfds[j].fd != -1) {
            send(pfds[j].fd, buff, strlen(buff), 0);
        }
    }
}

/*
 * Function to send messages from one client to other client/groups of clients
 * Arguments are integer indices of sender and pointer in poll array to integer array of receiver(s)
 * returns number of bytes sent
 */
void send_msg(int sender_index, int receiver_index, struct pollfd *pfds, char *buff) {
    // Declaration
    int j;
    char ident[10];
    
    // Send identity to client
    sprintf(ident, "%d", pfds[sender_index].fd);
    // check if receiver is connected
    if(pfds[receiver_index].fd != -1) {
        send(pfds[receiver_index].fd, ident, strlen(ident), 0);
        // Send message to client
        send(pfds[receiver_index].fd, buff, strlen(buff), 0);
    }
}
