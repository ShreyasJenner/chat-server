#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *print() {
    char msg[100];
    int bytes_read, i;
    char ch;
    
    i = 0;
    while(strcmp(msg,"stop\n")) {
        msg[i++] = getchar();

        if(msg[i-1]=='\n') {
            msg[i] = '\0';
            printf("%s",msg);
            i = 0;
        }
    }

    return NULL;
}

int main() {
    int i;
    pthread_t thread;

    pthread_create(&thread, NULL, print, NULL);

    i = 0;
    while(i<4) {
        printf("This World is working\n");
        sleep(3);
        i++;
    }


    pthread_join(thread, NULL);

    return 0;
}
