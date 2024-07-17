all:
	@gcc -o server \
		src/server.c \
		src/client_handling.c \
		src/error_handle.c \
		src/socket_handling.c \
		src/message.c
