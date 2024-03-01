#ifndef PEER_HANDLING_H
#define PEER_HANDLING_H

#include "header.h"

void display_peer_info(struct addrinfo *peers[PEER_NO]);

void read_peer_list(int fd, char peer_ip[PEER_NO][IP_WIDTH], char peer_port[PEER_NO][PORT_WIDTH]);

void get_address_info(struct addrinfo **peer, char *peer_ip, char *peer_port);

#endif
