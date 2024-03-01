## Flow [ Currently implemented for 2 client system ]
1. Server gets address information of peer 1
2. Server gets address information of peer 2
3. Server establishes connection to peer 1
4. Server establishes connection to peer 2
5. Reads msg from peer
6. Sends msg to other peer
7. Go to Step 5

## Peer Information
- Servers reads peer info from a file `peer_list`
- `peer_list` is a file containing peer ip addresses and their ports in the following format

| ip addr | port |
| ------- | ---- |
| localhost | 1234 |
| 192.168.22.4 | 4321 |

- ip addresses and ports are space separated
- each peer is on a new line

# To-do
- [x] Read peer list from file
- [x] Server gets address info of each peer
- [x] Server can display peer ip and port
- [ ] Server creates socket connection to peers


# Code Guidelines
- A C file can only have as header its own header file
    - Exception is server.c
- A header file can only call the main header file if necessary
