#include "node/node.hpp"

#include <thread>

void start_recv(Node *n, int sock) {
  std::string msg;
  while (true) {
    msg = n->recv_msg(sock);
    std::cout << msg << '\n';
    if (msg == "STOP") {
      break;
    }
  }
}

void start_send(Node *n, int sock) {
  std::string msg;
  while (true) {
    std::cin >> msg;
    n->send_msg(sock, msg);
    if (msg == "STOP") {
      break;
    }
  }
}

int main() {
  std::string ip, port;
  int sock;

  // Create node and start listening as server
  Node *n = new Node(SERVER, "localhost", "8080");
  n->start_node();
  sock = n->accept_conns();

  // NOTE: thread to recv messages
  std::thread t1(start_recv, n, sock);
  std::thread t2(start_send, n, sock);

  t1.join();
  t2.join();

  return 0;
}
