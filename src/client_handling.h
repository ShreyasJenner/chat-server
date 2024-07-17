#ifndef CLIENT_HANDLING_H
#define CLIENT_HANDLING_H

#include "header.h"

void display_client_req_info(struct addrinfo **clients, int size);

int get_host_ip(char *client_ip);

void get_host_port(char *client_port);

int get_address_info(struct addrinfo **client, char *client_ip, char *client_port);

#endif
