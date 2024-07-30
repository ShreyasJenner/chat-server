/* 
 * Program implements functions that deal with freeing memory, closing file descriptors and handling errors
 *
 * Implements the following functions:
 * close_fd(fd : int*) -> void
 * error_handle(context: char*) -> void
 */



#include "../headers/error_handle.h"




/* 
 * Function closes all active file descriptors present in the file descriptor array 
 * active file descriptors are non zero
 * integer array is initially memset with 0
 */
void close_fd(int *fd) {

    int i;                  /* iterator */

    i = 0;                  /* initialization */

    /* 
     * Close file descriptors that are active
     * active file descriptors are non zero
     */
    for(i=0;i<FD_NO && fd[i]!=0;i++) {
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
