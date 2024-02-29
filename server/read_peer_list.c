#include "read_peer_list.h"

void read_peer_list(int fd, char peer_ip[PEER_NO][IP_WIDTH], char peer_port[PEER_NO][PORT_WIDTH]) {
    /* Message */
    printf("Reading Peer list into peer_ip and peer_port\n");

    /* variables */
    int i,j,flag, bytes_read;
    char buff[1]; // store character read from file
    
    /* store bytes read */
    bytes_read = -1;

    /* Iterators */
    i = 0;
    j = 0;

    /* Flags */
    flag = 0;

    /* 
     * Loop reads 1 character from peer list file till EOF
     * Stores the character into peer_ip or peer_port
     */
    while((bytes_read = read(fd, buff, 1)) != 0) {
        /* Error handling */
        if(bytes_read==-1) {
            perror("Reading peer list file");
            exit(1);
        }
        
        if(flag) {
            if(buff[0] == '\n') {
                peer_port[i][j] = '\0';
                i++;
                j = 0;
                flag = 0;
            } else {
                peer_port[i][j++] = buff[0];
            }
        } else {
            if(buff[0] == ' ') {
                peer_ip[i][j] = '\0';
                j = 0;
                flag = 1;
            } else {
                peer_ip[i][j++] = buff[0];
            }
        }
    }
}
