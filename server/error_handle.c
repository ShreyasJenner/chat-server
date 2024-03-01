#include "error_handle.h"

/* Function closes size number of file descriptors present in the file descriptor array */
void close_fd(int *fd, int size) {
    /* Message */
    printf("Closing File Descriptors\n");

    int i;                  /* iterator */

    i = 0;                  /* initialization */

    /* Close file descriptors */
    for(i=0;i<size;i++) {
        close(fd[i]);
    }
}

/* Function is usually called for error handling when some system call fails
 * takes as argument a char* to a string that gives the context of the rror and exits the program
 */
void error_handle(char *context) {
    perror(context);
    exit(1);
}
