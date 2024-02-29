## Flow
- Server establishes connection to peer 1
- Server establishes connection to peer 2
- Reads msg from peer
- Sends msg to other peer

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
- [ ] Server gets address info of each peer
