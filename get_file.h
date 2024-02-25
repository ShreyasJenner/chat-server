#ifndef GET_FILE_H
#define GET_FILE_H

#include "header.h"

FILE* get_file_ptr(char *path, char *file_name);

int close_file_ptr(FILE *ptr);

#endif
