#include "client/client.hpp"

int main() {
  Client *c = new Client("localhost", "1234");

  c->start_client();

  c->connect_to("localhost", "8080");

  c->send_msg("hello");

  std::cout << c->recv_msg() << '\n';

  return 0;
}
