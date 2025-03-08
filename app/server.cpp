#include "server/server.hpp"

int main() {
  Server *s = new Server("localhost", "8080");
  s->start_server();
  s->accept_conns();

  auto ptr = s->get_user_data();

  std::cout << s->recv_msg(ptr->begin()->listeningSocket) << '\n';

  s->send_msg(ptr->begin()->sendingSocket, "Hello from server");

  return 0;
}
