all:
	@gcc -o client client.c socket.c
	@gcc -o server server.c socket.c
