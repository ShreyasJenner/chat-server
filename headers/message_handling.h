#ifndef MESSAGE_HANDLING_H
#define MESSAGE_HANDLING_H

#include "header.h"

void broadcast_msg(struct pollfd *pfds, char *buff, int active_clients, int curr_client);

void send_msg(int sender_index, int receiver_index, struct pollfd *pfds, char *buff);

#endif
