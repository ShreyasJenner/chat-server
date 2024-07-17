#include "message.h"

/*
 * Program implements message function that helps trace program running state 
 * 
 * Functions:
 * time_message() -> void
 * message(msg: char*) -> void
 */

/* Function logs the current time into the file */
void time_message() {
    FILE *fp = fopen("../logs/log.dump","a");
    
    /* if opening file didnt fail */
    if(fp!=NULL) {
        /* get time stamp in string form */
        time_t now = time(NULL);
        struct tm *tm = localtime(&now);
        fputc('\n', fp);    
        fputs(asctime(tm), fp); 
        
        fclose(fp);
    }
}

/* Function logs message with timestamp into log file*/
void message(char *msg) {
    FILE *fp = fopen("../logs/log.dump","a");
    
    /* if opening file didnt fail */
    if(fp!=NULL) {
        /* append the message to the file */
        fputs(msg, fp);
        fputc('\n', fp);
        fclose(fp);
    }
}
