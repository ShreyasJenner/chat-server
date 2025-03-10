#ifndef IRC_SERVER_HPP
#define IRC_SERVER_HPP

#include <iostream>
#include <thread>
#include <vector>

#include "node/node.hpp"

extern "C" {
#include <poll.h>
}

#define CMD_SYM '/'

class Users {
public:
  std::string username;
  std::string ip_addr;
  std::string port;
  int commSock;
};

class IRC_Server {
private:
  int current_conn_count;
  bool run;

  Node *server;

  std::vector<Users> user_data;
  struct pollfd pfds[SERVER_MAX_CONN];

public:
  IRC_Server(std::string ip_addr, std::string port);

  std::vector<Users> *get_user_data();

  void handle_connections();

  void send_msg_handling();

  void handle_recv();

  void run_IRC_Server();

  ~IRC_Server();
};

#endif // !IRC_SERVER_HPP
