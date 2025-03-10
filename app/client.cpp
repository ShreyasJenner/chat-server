#include "client/client.hpp"

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
  int sock;

  // create node and receive socket connected to server
  Node *n = new Node(CLIENT, "localhost", "1234");
  n->start_node();
  sock = n->connect_to("localhost", "8080");

  // NOTE: temp code to thread message handling
  std::thread t1(start_recv, n, sock);
  std::thread t2(start_send, n, sock);

  t1.join();
  t2.join();

  return 0;
}
