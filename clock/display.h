#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int open_display(void);
void display_time(int hours, int minutes, int seconds);
void display_colons(void);
void display_hours(int hours);
void display_minutes(int minutes);
void display_seconds(int seconds);
void close_display(void);

void display_12hr_time(int hours, int minutes, int seconds);
