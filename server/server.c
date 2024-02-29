/* Header Files */
#include "header.h"
#include "read_peer_list.h"

int main() {
    /* variables */    
    int fd;                           // file descriptor
    int bytes_read;                   // store bytes read 
    int i, j;                         // Iterators
    int flag;                         // Flag
    char buff[BUF_SIZE];              // buffer
    char peer_ip[PEER_NO][IP_WIDTH];        // store peer ip addresses
    char peer_port[PEER_NO][PORT_WIDTH];       // store 4 digit peer ports


    /* Initialize variables */
    bytes_read = -1;

    /* Open peer list file */
    if((fd = open("peer_list",O_RDONLY,0))<0) {
        perror("Opening peer list file");
        exit(1);
    }
    
    /* store peer list into peer_ip and peer_port */
    read_peer_list(fd, peer_ip, peer_port);
    

    /* Close file descriptors */
    close(fd);

    return 0;
}
