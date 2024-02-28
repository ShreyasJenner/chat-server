#!/bin/bash

while :
do
    msg=$(nc -l -p 4321)
    
    case "$msg" in
        stop)echo "Peer closed connection";
            break;
            ;;
        
        send)echo "Peer sending file";
            file=$(nc -l -p 1234);
            touch "$file";
            content=$(nc -l -p 1234);
            echo "$content" > "$file";
            echo "Contents written to file $file";
            ;;

        *)echo -n "$msg" >&1;
            ;;
    esac
done
