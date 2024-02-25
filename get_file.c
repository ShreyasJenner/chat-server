#include "get_file.h"

/*
 * Function takes file path and file name as arguments
 * Opens a file pointer to the file and returns it
 * Close_file_ptr should also be called after using file pointer
 * if this function is called
 */
FILE* get_file_ptr(char *path, char *file_name) {
    chdir(path);
    FILE *ptr = fopen(file_name,"r");

    if(ptr!=NULL)
        printf("success\n");
    else
        printf("fail\n");
}

/* 
 * Function closes file pointer
 * Returns fclose value
 */
int close_file_ptr(FILE *ptr) {
    return fclose(ptr);
}
