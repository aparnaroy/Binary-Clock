#include "display.h"
#include <stdio.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int lastSignal=0;
void interrupt_handler(int sig){
//    printf("Got signal: %d!\n",sig);
    if(lastSignal==sig) {
        lastSignal=-1;
    } else {
        lastSignal=sig;
    }
}

/*
int main(){
    // you'd generally only trap the signals you cared about. See "man 7 signal" for a list
    for(int sig =1; sig<32; sig++) {
        signal(sig, interrupt_handler);
    }
    while(lastSignal >= 0) {
        if(lastSignal) {
            printf("last signal was: %d. Send it again to exit.\n",lastSignal);
        } else {
            printf("signal me using 'kill -SIGNUM %ld'!\n",(long int)getpid());
        }
        sleep(1);
    }
    return 0;
}
*/

int main(void) {
    open_display();

    int hours, minutes, seconds;

    signal(SIGUSR1, interrupt_handler);
    /*
    if(lastSignal) {
        display_12hr_time(hours, minutes, seconds);
    }
    else {
        display_time(hours, minutes, seconds);
    }
    */
    
    //    while(lastSignal >= 0) {    
        while (!(scanf("%d:%d:%d", &hours, &minutes, &seconds) < 3)) {
            if(lastSignal) {
                display_12hr_time(hours, minutes, seconds);
            }
            else {
                display_time(hours, minutes, seconds);
            }
        }
//    }

    close_display();
   
    return 0;
}
