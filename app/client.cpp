#include "client/client.hpp"

int main() {
  Client *c = new Client();

  c->connect_to("localhost", "8080");

  c->send_msg("hello");

  return 0;
}
