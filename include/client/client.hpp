#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

extern "C" {
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
}

class Client {
private:
  int sendingSockfd, listeningSockfd;
  std::string ip_addr;
  std::string port;

public:
  void connect_to(std::string ip_addr, std::string port);

  void send_msg(std::string msg);

  void recv_msg();
};

#endif // !CLIENT_HPP
