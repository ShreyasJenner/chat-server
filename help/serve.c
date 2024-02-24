#include "header.h"

void error_handle(int error_code, char *error_str) {
    if(error_code!=0 && errno!=EEXIST) {
        perror(error_str);
        exit(1);
    }
}

int main() {
    int fd,pid;
    char buffer[100];

    error_handle(mknod(PIPE, S_IFIFO | 0640,0),"Creating pipe");

    while(1) {
        pid = fork();
        if(pid!=0) {
            fd = open(PIPE, O_RDONLY);
            error_handle(fd,"Parent");
            read(fd, buffer, 100);
            printf("%s\n",buffer);
            close(fd);
        } else {
            fd = open(PIPE, O_WRONLY);
            error_handle(fd, "Child");
            scanf("%[^\n]",buffer);
            write(fd, buffer, strlen(buffer));
            close(fd);
        }
    }
    return 0;
}
