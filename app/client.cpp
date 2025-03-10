#include "client/client.hpp"

#include <thread>

void start_recv(Client *c) {
  std::string msg;
  while (true) {
    msg = c->recv_msg();
    std::cout << msg << '\n';
    if (msg == "STOP") {
      break;
    }
  }
}

void start_send(Client *c) {
  std::string msg;
  while (true) {
    std::cin >> msg;
    c->send_msg(msg);
    if (msg == "STOP") {
      break;
    }
  }
}

int main() {
  Client *c = new Client("localhost", "1234");

  c->start_client();

  c->connect_to("localhost", "8080");

  // NOTE: temp code to thread message handling
  std::thread t1(start_recv, c);
  std::thread t2(start_send, c);

  t1.join();
  t2.join();

  return 0;
}
