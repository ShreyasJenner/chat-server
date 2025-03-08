#include "server/server.hpp"

int main() {
  Server *s = new Server("localhost", "8080");
  s->start_server();
  s->accept_conns();

  std::cout << s->recv_msg() << '\n';

  return 0;
}
