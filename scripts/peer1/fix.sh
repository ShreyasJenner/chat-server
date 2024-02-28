# Run script if errors are ocurring

pid=$(ps -e | grep nc | awk '{ print $1 }')
pid=$( echo "$pid" | tr '\n' ' ');

echo "$pid"
kill "$pid"
