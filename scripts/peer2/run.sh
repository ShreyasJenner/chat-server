#!/bin/bash

# Kill all processes started by this process
trap 'kill $(jobs -p) 2>/dev/null' EXIT

./server.sh &
./client.sh
