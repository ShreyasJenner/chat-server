#include "input_parse.h"

/* program takes 3 character arrays as argument 
 * takes input as path of file
 * checks for errors
 * parses its directory path relative to current directory
 * copies to the passed string the parsed string 
 * RETURN VALUES:
 * returns 0 on success
 * returns -1 on error
 */

int file_name_parse(char *input, char *path, char *file_name) {
    /* Declaration */
    int i,len,j;

    /* Initialization */
    i = 0;
    j = 0;
   
    /* Store string length */
    len = strlen(input);

    /* 
     * Check for invalid path format
     * return -1 on bad format
     */
    while(input[i]!='\0') {
        if(input[i]==' ' && input[i-1]!='\\')
            return -1;
        i++;
    }

    /* Get last / character's index */
    i = len;
    while(i>=0) {
        if(input[i]=='/')
            break;
        i--;
    }

    /* Copy path name to path arg */ 
    while(j<=i) {
        path[j] = input[j];
        j++;
    }
    path[j] = '\0';
    
    /* and file name to file_name arg */
    j = 0;
    i++;
    while(i<len) {
        file_name[j] = input[i];
        j++;
        i++;
    }
    file_name[j] = '\0';

    return 0;
}
