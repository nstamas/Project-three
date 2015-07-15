/*Assignment 3 simplealarm.c
 *by Nick Stamas Section 1
 *
 *This program enters an infinte loop where an alarm is set to go off
 *every second. During this time the processor is finding and printing
 *every prime integer greater than 1000000. Sigaction is used to 
 *respond to the to alarm signal. Every time the alarm goes off
 *sigaction calls a function taht prints out the current time.
 *
 */

#define _OPEN_SYS
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

/*Declartion of the varible used to store the current time to be printed*/
time_t currtime;

/*catchsig is a funtion that is called when an alarm releases a signal.
 * 	When a signal is released the function will print the current
 *	time.
 *Parameters:
 * sigalrm the signal released when an alarm goes off.
 */
void catchsig(int sigalrm){
	time(&currtime);
	printf ("current time is: %s", ctime (&currtime));
	alarm(1);
}

/*main the main function that keeps our program in an infinite loop,
 *	while also finding and printing all the prime integers greater 
 *	than 1000000. 
 */
int main(){

	/*A declaration of a sigation struct*/
	struct sigaction sact;
	sigemptyset(&sact.sa_mask);
	sact.sa_flags = 0;
	/*assigning what function is called when sigaction detects a signal*/
	sact.sa_handler = catchsig;
	sigaction(SIGALRM, &sact, NULL);

	/*Setting an alarm to go off every second*/
	alarm(1);

	/*Instantiation and declaration of prime varible. This will be
	  the first number greater than 1000000 we will check to be a 
	  prime number*/
	int prime = 1000001;
	/*Declaration of a varible used in the prime finding algorithm*/
	int startfactor;
	/*Simple int varible used as a flag to illustrate whether or not a number is prime*/
	int notprime = 0;

	/*Infinte loop*/
	while(1){
		
		/*Instantiate flag varible*/
		notprime = 0;

		/*A simple algorithm used to determine whether or not a number is prime or not.
		  In this algroithm the number to classify is divide by every number less than it in
		  order to find if it has any factors. When all numbers less than the one we are trying
		  to classify have been checked and the flag varible has not been set to one, we know we
		  have found a prime number. If a prime number is found we will print it out to the console*/
		for(startfactor = prime - 1; startfactor > 1; startfactor --){
			/*Checking the remainder of the number to classify*/
			if (prime % startfactor == 0){
				/*Number is not prime so the flag is set to one*/
				notprime = 1;
			}
		}
		/*If number is prime it is printed out*/
		if(notprime == 0){
			printf("%d ", prime);
		}
		/*Number to find the next prime*/
		prime = prime + 1;
	}
	
	return (0);
}

