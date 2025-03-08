#include "client/client.hpp"

// Function to connect to a system with the given ip address over the given port
void Client::connect_to(std::string ip_addr, std::string port) {
  struct addrinfo hints, *res;
  int err;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  err = getaddrinfo(ip_addr.c_str(), port.c_str(), &hints, &res);
  if (err != 0) {
    perror("Error populating address struct");
    exit(1);
  }

  // make a socket
  this->sendingSockfd =
      socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  err = connect(sendingSockfd, res->ai_addr, res->ai_addrlen);
  if (err != 0) {
    perror("Error connecting to socket");
    exit(1);
  }
}

// Function to send a message to the server
void Client::send_msg(std::string msg) {
  int len;

  // Send the length of the message before sending the message
  len = msg.length();
  send(this->sendingSockfd, &len, sizeof(len), 0);
  send(this->sendingSockfd, msg.c_str(), msg.length(), 0);
}

// Function to receive a message from the server
void Client::recv_msg() {
  int len, err;

  // receive message length
  err = recv(this->sendingSockfd, &len, sizeof(len), 0);
  if (err != sizeof(int)) {
    perror("Error receiving message length");
  }
  char buff[len];

  // receive message
  err = recv(this->sendingSockfd, buff, len, 0);
  if (err != len) {
    perror("Error receiving message");
  }

  std::cout << "Msg: " << buff << '\n';
}
