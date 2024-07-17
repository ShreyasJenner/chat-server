#ifndef CLIENT_HANDLING_H
#define CLIENT_HANDLING_H

#include "header.h"

void display_client_req_info(struct addrinfo **clients, int size);

int read_client_list(char client_ip[CLIENT_NO][IP_WIDTH], char client_port[CLIENT_NO][PORT_WIDTH], int active_clients);

int get_address_info(struct addrinfo **client, char *client_ip, char *client_port);

#endif
