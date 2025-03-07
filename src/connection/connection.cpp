#include "connection/connection.hpp"

// Parametric constructor to store ip address and port
Connection::Connection(std::string ip_addr, std::string port) {
  this->ip_addr = ip_addr;
  this->port = port;
}

// Function to create a socket on a port and make the current node a server
void Connection::start_server() {

  int err;
  struct addrinfo hints, *res;

  // load address structs
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  err = getaddrinfo(NULL, this->port.c_str(), &hints, &res);
  if (err != 0) {
    perror("Error filling address structs");
    exit(1);
  }

  // create a listening socket
  this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (this->serverSocket < 0) {
    perror("Error creating listening socket");
    exit(1);
  }

  // bind the socket to the given port
  err = bind(this->serverSocket, res->ai_addr, res->ai_addrlen);
  if (err != 0) {
    perror("Error binding socket to port");
    exit(1);
  }

  // start listening on the socket
  listen(this->serverSocket, MAX_CONN);
}

// Function to accept connections from the server socket
void Connection::accept_conns() {
  struct sockaddr_storage other_addr;
  struct sockaddr_in *ptr;
  socklen_t addr_size;

  int otherSock;

  addr_size = sizeof other_addr;
  otherSock =
      accept(this->serverSocket, (struct sockaddr *)&other_addr, &addr_size);
  if (otherSock == -1) {
    perror("Error accepting connection to socket");
    exit(1);
  }

  // create an object of users class and populate it
  Users *u = new Users();
  ptr = (struct sockaddr_in *)&other_addr;
  u->port = ptr->sin_port;
  u->ip_addr = ptr->sin_addr.s_addr;
  u->socket = otherSock;

  // push the user object into the vector
  this->user_data.push_back(*u);
}
