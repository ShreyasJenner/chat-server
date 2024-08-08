/*
 * Program implements log function that helps trace program running state 
 * 
 * Functions:
 * time_log() -> void
 * log(msg: char*) -> void
 */

#include "../headers/log.h"

/* Function logs the current time into the file */
void time_log() {
    FILE *fp;
    fp = fopen("logs/log.dump","a");
    
    /* if opening file didnt fail */
    if(fp!=NULL) {
        /* get time stamp in string form */
        time_t now = time(NULL);
        struct tm *tm = localtime(&now);
        fputc('\n', fp);    
        fputs(asctime(tm), fp); 
        
        fclose(fp);
    }
    else {
        printf("Logging failed\n");
    }
}

/* Function logs log with timestamp into log file*/
void log_msg(char *msg) {
    FILE *fp = fopen("logs/log.dump","a");
    
    /* if opening file didnt fail */
    if(fp!=NULL) {
        /* append the log to the file */
        fputs(msg, fp);
        fputc('\n', fp);
        fclose(fp);
    }
    else {
        printf("Logging failed\n");
    }
}
