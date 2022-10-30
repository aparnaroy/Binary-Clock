# Binary_Clock
A clock that displays time values in binary.

## Program Functionalities:
The basic "clock" program reads times from stdin (in the form of HH:MM:SS) and displays them as a 24-hr format (HH ranges from 0-23, MM and SS range from 0-59).
1) **Manual Input Clock:** The user continuously manually inputs times and the clock changes display based on the input
2) **Real-Time Clock:** A shell script called "clock.sh" continuously prints the current time, which is displayed by the "clock" executable
    * In addition, the "clock" program/process accepts signals from the operating system. Each time the “usr1” signal is received, the program **toggles 12-hour mode**:
      * In 12-hour mode, only values for hours from 1-12 are displayed (instead of 0-23), with the background and colon **colors reversed** during the hours after noon through midnight

## Binary Clock Display Visuals:
<img width="664" alt="Binary Clock Display" src="https://user-images.githubusercontent.com/94129173/198888026-98070526-dabc-48a7-a574-a39f1bb24406.png">

## Program Components:
* Bash script **clock.sh** that once/second prints the time in the 24-hour clock format (HH:MM:SS)
* The following files are used to build a program called **clock** that continuously reads lines from stdin (either from user input or from the output of the clock.sh shell script) and displays them:
  * **display.c** : Includes the following functions:
    * **int open_display(void)** : creates a suitable environment to draw the clock as described
    * **void display_time(int hours, int minutes, int seconds)** : displays the time using the below helpers:
      * **void display_colons(void)** : draws the colons
      * **void display_hours(int hours)** : draws the hours
      * **void display_minutes(int minutes)** : draws the minutes
      * **void display_seconds(int seconds)** : draws the seconds
    * **void close_display(void)** : shuts down the clock display
  * **display.h** : includes prototypes for the above functions for use in **main.c** 
  * **main.c** : contains the **main** function, which continuously reads lines from stdin and displays them using the function **display_time**
* A **Makefile** with the following rules:
  * Rules to compile .c files into .o files (to create display.o and main.o)
  * An **all** rule that combines all .o files into an executable clock
  * A **clean** rule that removes the executable clock and all .o files
  * A **run** rule that runs the shell script and pipes the output into the **clock** program

## How to Run the Program:
### Manual Input Clock: 
1) Type the following commands in the command line:   
      > $ make  
	      $ ./clock  
2) Type in the time in HH:MM:SS format and press Enter 
    * The 24-hour clock will then display the inputted time (and then you can input another time again)
3) To exit the program, type in anything that is not of the form HH:MM:SS and press Enter

### Real Time Clock:
1) Type the following command in the command line:    
      > $ make run
      * The 24-hr clock display will then pop up, continuously displaying the current time
2) To toggle back and forth between the 24-hr and 12-hr versions of the clock:
    * On a new terminal tab/window, type the following commands:    
      > $ ps -U {username}     
		    $ kill -usr1 {PID#_of_running_clock_process}
3) To exit the program, press CTRL^C
