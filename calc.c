/*Assignment 3 calc.c
 *by Nick Stamas section 1
 *
 *This program enters an infinite loop where a user is able to
 *input two integers followed by an operator(+,-,*,/). The program
 *will then calculate the operation of the two intergers and print 
 *out the answer. If the user inputs anthing other than the four operators
 *above during the operator call, the program will prompt the user that
 *they have entered any illegal operator. Sigaction has been implemented to 
 *detect a divde by zero and to detect if the user has input ctrl c.
 *If the user tries to perform a divde by zero, the program will inform 
 *the user they have performed a divide by zero and will then exit the program.
 *If the user types ctrl c the program will inform the user of the number of 
 *operation they have perfomred and will then exit the program.
*/
#define _OPEN_SYS
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/*Declaration of the varible used to store the number of operations*/
int count;

/*catchZero is function that is called when a divde by zero signal
 *	is released. This functions informs the user they have 
 *	attempted to divde by zero and then exits the program.
 *Parameters:
 *  sigfe: The signal that is released when a divde by zero occurs
 */
void catchZero(int sigfpe){
	printf("You attempted to divde by zero!\n");
	exit(0);
}

/*catchzEnd is function that is called when a user enters ctrl
 *	c. This functions informs the user of the number of  
 *	operations they have performed and then exits the program.
 *Parameters:
 *  sigint: The signal that is released when ctrl c is pressed.
 */
void catchEnd(int sigint){
	printf(" You have completed %d operations!\n", count);
	exit(0);
}

/*main the function used to create the infinite loop and ask the operation they
 *	want calculated.
 *Parameters: 
 * argc: number of arguments passed in through the terminal
 * argv[]: an holding the arguments passed through the terminal.*/
int main(int argc, char *argv[]){

    /*A declaration of a sigation struct*/
    struct sigaction sac1;
    sigemptyset(&sac1.sa_mask);
    sac1.sa_flags = 0;
    /*assigning what function is called when sigaction detects a fpe signal*/
    sac1.sa_handler = catchZero;
    sigaction(SIGFPE, &sac1, NULL);
    
    /*A declaration of a sigation struct*/
    struct sigaction sac2;
    sigemptyset(&sac2.sa_mask);
    sac2.sa_flags = 0;
    /*assigning what function is called when sigaction detects an int signal*/
    sac2.sa_handler = catchEnd;
    sigaction(SIGINT, &sac2, NULL);

    /*instantiate the intial operation count to zero*/
    count = 0;

    while(1){

	int buffsize = 80;
	/*Character buffer array where user input will be stored*/
	char buffer [buffsize];
	/*Prompt user for the first integer*/
	printf("Please enter your first integer: ");
	/*Declartion of first integer variable*/
	int firstnum;
	/*Store user input in character buffer array*/
	fgets (buffer, buffsize, stdin);
	/*Convert user input into an integer and instantiate the first integer variable*/
	firstnum = atoi(buffer);
	/*Prompt user for the second integer*/
	printf("Please enter your second integer: ");
	/*Declartion of second integer variable*/
	int secondnum;
	/*Store user input in character buffer array*/
	fgets (buffer, buffsize, stdin);
	/*Convert user input into an integer and instantiate the second integer variable*/
	secondnum = atoi(buffer);
	/*Declartion of operator variable*/
	char operator;
	/*Prompt user for operator input*/
	printf("Please enter the operation you would like to perform: ");
	/*Store user input in character buffer array*/
	fgets (buffer, buffsize, stdin);
	/*Instantiate operator varible to the operator the user input*/
	operator = buffer[0];
	
	/*Check what operator was input and then calculate the correct answer 
	  based on previous input. If an illegal operator was input, the user
          will be informed, and an addition operation will be performed on
	  default.*/
	if(operator == '+'){
		printf("%d\n", firstnum + secondnum);
		count++;
	}else if (operator == '-'){
		printf("%d\n", firstnum - secondnum);
		count++;
	}else if (operator == '*'){
		printf("%d\n", firstnum * secondnum);
		count++;
	}else if (operator == '/'){
		printf("%d\n", firstnum / secondnum);
		count++;
	}else {
		printf("You input an illegal operator!\n");
		printf("%d\n", firstnum + secondnum);
		count++;
	}

     }

     return (0);
}
	
