## Flow [ Currently implemented for 2 client system ]
1. Server gets address information of client 1
2. Server gets address information of client 2
3. Server establishes connection to client 1
4. Server establishes connection to client 2
5. Reads msg from client
6. Sends msg to other client
7. Go to Step 5

## Peer Information
- Servers reads client info from a file `client_list`
- `client_list` is a file containing client ip addresses and their ports in the following format

| ip addr | port |
| ------- | ---- 
| localhost | 1234 |
| 192.168.22.4 | 4321 |

- ip addresses and ports are space separated
- each client is on a new line

# To-do
- [x] Read client list from file
- [x] Server gets address info of each client
- [x] Server can display client ip and port
- [x] Server creates socket poll array for listening 
- [x] Server starts listening on socket
- [x] Clients send to server instead of other client directly [server handles sending of messages to other client]
- [x] Allow more than two clients to communicate with the server
- [ ] Communciation allowed only when all clients connect. Replace so that any client can communicate with another even if all clients haven't logged in
- [ ] Modify program to allow for communication through network as well (NAT??)
- [ ] Allow dynamic retrieval of ip address so that client\_list file need not be manually modified


# Code Guidelines
- A C file can only have as header its own header file
    - Exception is server.c
- A header file can only call the main header file if necessary
