#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <vector>

extern "C" {
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
}

#define MAX_CONN 10

class Users {
public:
  std::string ip_addr;
  int port;
  int socket;
};

class Connection {
private:
  std::string ip_addr;
  std::string port;

  int serverSocket;

  std::vector<Users> user_data;

public:
  Connection(std::string ip_addr, std::string port);

  void start_server();

  void accept_conns();
};

#endif // !CONNECTION_HPP
