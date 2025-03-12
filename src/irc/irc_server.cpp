#include "irc/irc_server.hpp"

// Constructor for IRC Server class
// NOTE: temporary ip address and port used for server node
IRC_Server::IRC_Server(std::string ip_addr, std::string port) {
  // initalize the bookeeping variables
  this->run = true;
  this->current_conn_count = 0;

  // set all the fds in the polling struct array to negative 1
  int i;
  for (i = 0; i < SERVER_MAX_CONN; i++) {
    this->pfds[i].fd = -1;
  }

  // create and start server
  this->server = new Node(SERVER, ip_addr, port);
  this->server->start_node();

  // banner message
  std::cout << "IRC Server starting\n";
}

// Getter function to get pointer to vector of user data
std::vector<Users> *IRC_Server::get_user_data() { return &this->user_data; }

// Function to handle accepting of connections to server
void IRC_Server::handle_connections() {
  int sockfd;
  std::string ip_addr, port, username;

  // accept connections as long as server is running
  // accept connections only if connections are available
  while (this->run && this->current_conn_count < SERVER_MAX_CONN) {

    // accept a connection to the server and receive the socket
    sockfd = this->server->accept_conns();

    // create a Users object, populate it, and store it in the vector
    Users u;

    // receive the client details and store it in the user object
    u.channels.push_back(this->server->recv_msg(sockfd));
    u.username = this->server->recv_msg(sockfd);
    u.ip_addr = this->server->recv_msg(sockfd);
    u.port = this->server->recv_msg(sockfd);
    u.commSock = sockfd;
    u.pollIdx = this->current_conn_count;
    this->user_data.push_back(u);

    // Add the user socket to the polling array
    this->pfds[this->current_conn_count].fd = sockfd;
    this->pfds[this->current_conn_count].events = POLLIN;

    // increment the count of user connections
    this->current_conn_count++;
  }
}

// Function to handle receiving of messages for all sockets
void IRC_Server::handle_recv() {
  int num_events, i;
  std::string msg, channel, username;

  // infinite loop that runs while server has not shut down
  while (this->run) {
    // poll the sockets every 1 second
    num_events = poll(this->pfds, this->current_conn_count, 2000);

    // iterate through the array handling all polling events
    i = 0;
    while (num_events > 0 && i < SERVER_MAX_CONN) {
      // if the socket has data that can be read, read the data
      if (this->pfds[i].revents & POLLIN) {

        // receive the client messages
        channel = this->server->recv_msg(this->pfds[i].fd);
        username = this->server->recv_msg(this->pfds[i].fd);
        msg = this->server->recv_msg(this->pfds[i].fd);

        // check if the message is a stop sign, if it is, then close the socket
        if (msg == "STOP") {
          this->handle_client_exit(i);
        }

        // NOTE: temp code that prints the received data
        std::cout << "Channel : " << channel << '\n';
        std::cout << "Username: " << username << '\n';
        std::cout << "Message: " << msg << '\n';
      }

      // increment i to check the next socket
      i++;
      num_events--;
    }
  }
}

// Function to handle when client sends STOP msg
void IRC_Server::handle_client_exit(int index) {
  std::cout << "Client " << this->user_data[index].username
            << " ending communication\n";

  // send an acknowledging message to the client
  this->server->send_msg(this->user_data[index].commSock, "STOP");

  // close the socket and remove the value from the socket
  this->server->close_sockets(this->user_data[index].commSock);
  this->user_data.erase(this->user_data.begin() + index);

  // set the value in the poll struct to 0
  this->pfds[index].fd = -1;
}

// Function to handle sending of messages to clients
void IRC_Server::handle_send() {
  std::string msg;

  // run function while the server is up
  while (this->run) {
    std::cin >> msg;

    // iterate through users and send message
    for (auto user : this->user_data) {
      this->server->send_msg(user.commSock, msg);
    }
  }
}

// Function to run the irc server
void IRC_Server::run_IRC_Server() {
  std::cout << "Running IRC Server\n";

  // thread to handle accepting connections
  std::thread t1(&IRC_Server::handle_connections, this);

  // thread to handle receiving of messages
  std::thread t2(&IRC_Server::handle_recv, this);

  // thread to handle sending of messages
  std::thread t3(&IRC_Server::handle_send, this);

  // wait for the thread to finish
  t1.join();
  t2.join();
  t3.join();
}

// Destructor to deallocate resources
IRC_Server::~IRC_Server() {
  std::cout << "Closing IRC Server\n";

  // shutdown and close the communication sockets
  for (auto user : this->user_data) {
    if (user.commSock != -1) {
      this->server->close_sockets(user.commSock);
    }
  }

  // remove the node
  delete this->server;
}
