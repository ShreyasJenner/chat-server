# Run script if errors are ocurring

pid=$(ps -e | grep nc | awk '{ print $1 }')
kill "$pid"
