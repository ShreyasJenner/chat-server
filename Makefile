all:
	@gcc -o client client.c socket.c input_parse.c
	@gcc -o server server.c socket.c input_parse.c
