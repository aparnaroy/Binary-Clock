#include "ncurses.h"
#include "display.h"
#include <stdio.h>

#define BLACK 4
#define WHITE 1
#define BLUE 5
#define GREEN 3
#define RED 2

int open_display(void) {
    initscr();
    
    int val;

    if (initscr() == NULL) {
        val = 0;
    }
    else {
        val = 1;
    }
    
    start_color();
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(RED, COLOR_RED, COLOR_RED);

    return val;
}

int mode = 0;

void display_time(int hours, int minutes, int seconds) {
    mode = 0;
    attron(COLOR_PAIR(BLACK));
    for (int x=0; x<8; x++) {
        for (int y=0; y<8; y++) {
            attron(COLOR_PAIR(BLACK));
            mvaddch(y,x,' ');
        }
    }
    clear();
    refresh();

    display_colons();
    refresh();
    display_hours(hours);
    refresh();
    display_minutes(minutes);
    refresh();
    display_seconds(seconds);
    refresh();
    attron(COLOR_PAIR(BLACK));
}

void display_12hr_time(int hours, int minutes, int seconds) {
    mode = 0;
    clear();
    /*
    attron(COLOR_PAIR(WHITE));
    for (int x=0; x<100; x++) {
        for (int y=0; y<100; y++) {
            mvaddch(y,x,' ');
        }
    }
    */
    
    if (hours>=12 && hours<24) {
        mode = 1;
        wbkgd(stdscr, COLOR_PAIR(WHITE));
        refresh();
        display_colons();
        refresh();
        if (hours == 12) {
            display_hours(12);
        }
        else {
            display_hours(hours-12);
        }
        refresh();
        display_minutes(minutes);
        refresh();
        display_seconds(seconds);
        refresh();
    }
    else {
        mode = 0;
        wbkgd(stdscr, COLOR_PAIR(BLACK)); 
        attron(COLOR_PAIR(BLACK));
        display_colons();
        refresh();
        display_hours(hours);
        refresh();
        display_minutes(minutes);
        refresh();
        display_seconds(seconds);
        refresh();
    }
}

void display_colons(void) {
    if (mode == 0) {
        attron(COLOR_PAIR(WHITE));
    }
    else if (mode == 1) {
        attron(COLOR_PAIR(BLACK));
    }
    mvaddch(6,2,'#');
    mvaddch(6,3,'#');
    mvaddch(6,5,'#');
    mvaddch(6,6,'#');
    mvaddch(5,2,'#');
    mvaddch(5,3,'#');
    mvaddch(5,5,'#');
    mvaddch(5,6,'#');
    mvaddch(3,2,'#');
    mvaddch(3,3,'#');
    mvaddch(3,5,'#');
    mvaddch(3,6,'#');
    mvaddch(2,2,'#');
    mvaddch(2,3,'#');
    mvaddch(2,5,'#');
    mvaddch(2,6,'#');
    refresh();
}

void display_hours(int hours) {
    int binary[6];
    int i = hours;
    // k represents the index in the binary array, and the array gets filled from right to 
    // left
    int k = 5;
    // This finds the binary number that represents the decimal hours value
    while (i != 0) {
        if (i % 2 == 0) {
            binary[k] = 0;
        }
        else {
            binary[k] = 1;
        }
        i = i / 2;
        k = k - 1;
    }

    // This starts at the bottom row of the grid (where y = 7) and goes up one each time,
    // checking to see if there is a 1 for that spot in the binary array and filling it 
    // color if there is
    attron(COLOR_PAIR(BLUE));
    int y = 7;
    for (int j=5; j>=0; j--) {
        if (binary[j] == 1) {
            // The hours will be represented on x = 6, or row 6
            mvaddch(y,1,'#');
        }
        y = y - 1;
    }
    refresh();
}

void display_minutes(int minutes) {
    // There's 6 places the binary number could possibly have since 59 minutes is the max
    int binary[6];
    int i = minutes;
    int k = 5;
    while (i != 0) {
        if (i % 2 == 0) {
            binary[k] = 0;
        }
        else {
            binary[k] = 1;
        }
        i = i / 2;
        k = k - 1;
    }
    
    attron(COLOR_PAIR(GREEN));
    int y = 7;
    for (int j=5; j>=0; j--) {
        if (binary[j] == 1) {
            mvaddch(y,4,'#');
        }
        y = y - 1;
    }
    refresh();
}

void display_seconds(int seconds) {
    // There's 6 places the binary number could possibly have since 59 minutes is the max
    int binary[7];
    int i = seconds;
    int k = 6;
    while (i != 0) { 
        if (i % 2 == 0) {
            binary[k] = 0;
        }
        else {
            binary[k] = 1;
        } 
        i = i / 2;
        k = k - 1;
    }
    
    attron(COLOR_PAIR(RED));
    int y = 7;
    for (int j=6; j>=0; j--) {
        if (binary[j] == 1) {
            mvaddch(y,7,'#');
        } 
        y = y - 1;
    }
    refresh();
}

void close_display(void) {
    clear();
    refresh();
    sleep(1);
    endwin();
}
