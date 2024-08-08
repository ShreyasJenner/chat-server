all:
	@gcc -o server \
		src/server.c \
		src/client_handling.c \
		src/error_handle.c \
		src/socket_handling.c \
		src/message.c

	@gcc -o client \
		client_src/client.c
