#ifndef READ_PEER_LIST_H
#define READ_PEER_LIST_H 

#include "header.h"

void read_peer_list(int fd, char peer_ip[PEER_NO][IP_WIDTH], char peer_port[PEER_NO][PORT_WIDTH]);

#endif
