#include "display.h"
#include <stdio.h>

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int lastSignal=0;
void interrupt_handler(int sig){
    if(lastSignal==sig) {
        lastSignal=-1;
    } else {
        lastSignal=sig;
    }
}

int main(void) {
    open_display();

    int hours, minutes, seconds;

    signal(SIGUSR1, interrupt_handler);
    
    while (!(scanf("%d:%d:%d", &hours, &minutes, &seconds) < 3)) {
        if(lastSignal) {
            display_12hr_time(hours, minutes, seconds);
        }
        else {
            display_time(hours, minutes, seconds);
        }
    }

    close_display();
   
    return 0;
}
