#include "server/server.hpp"

#include <thread>

void start_recv(Server *s, std::vector<Users> *ptr) {
  std::string msg;
  while (true) {
    msg = s->recv_msg(ptr->begin()->listeningSocket);
    std::cout << msg << '\n';
    if (msg == "STOP") {
      break;
    }
  }
}

void start_send(Server *s, std::vector<Users> *ptr) {
  std::string msg;
  while (true) {
    std::cin >> msg;
    s->send_msg(ptr->begin()->sendingSocket, msg);
    if (msg == "STOP") {
      break;
    }
  }
}

int main() {
  Server *s = new Server("localhost", "8080");
  s->start_server();
  s->accept_conns();

  auto ptr = s->get_user_data();

  // NOTE: thread to recv messages
  std::thread t1(start_recv, s, ptr);
  std::thread t2(start_send, s, ptr);

  t1.join();
  t2.join();

  return 0;
}
