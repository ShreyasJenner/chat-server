#ifndef SOCKET_H
#define SOCKET_H

void error_handle(int code, char *str);

void get_host_data(struct addrinfo **server,char *host,char *port);

void print_ip(struct addrinfo *server);

int create_socket(struct addrinfo *server);

void recv_msg(struct addrinfo *server, int sockfd);

void send_msg(struct addrinfo *server);
#endif
