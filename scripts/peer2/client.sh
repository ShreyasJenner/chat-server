declare -i port

# Store ip addresses
self=$(hostname -i)
peer=$(cat peer)
port=4321

# Functions
function send_msg() {
    nc -c "$self" "$port" < $1 
}

function store_msg() {
    echo "$1" > msg
}


echo "Starting Connection";
while :
do
    read -p "Me$ " var
    case "$var" in
        send)store_msg "$var"; 
            send_msg msg;
            echo "Enter file name";
            read var;
            store_msg "$var";
            send_msg msg;
            send_msg "$var";
            ;;

        stop)store_msg "$var";
            send_msg msg;
            break;
            ;;

        view*)echo "$var";
            ;;
    
        *)echo -en "\r$self:$port"$ "$var" "\nMe$ " > msg;
            send_msg msg;
            ;;
    esac
done
