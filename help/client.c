#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define PIPE "LAYER"

void error_handle(int error_code, char *error_str) {
    if(error_code!=0 && errno!=EEXIST) {
        perror(error_str);
        exit(1);
    }
}

int main() {
    int fd, bytes_sent;
    char buffer[100];

    while(1) {
        fd = open(PIPE, O_WRONLY);
        error_handle(fd, "File Descriptor");
        scanf("%[^\n]",buffer);
        bytes_sent = write(fd, buffer, strlen(buffer));
        close(fd);
    }

    return 0;
}
