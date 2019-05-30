#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include<sys/wait.h> 



// void sigCathcher(int sig)
// {
//     kill(child_pid,SIGKILL);
// }


int main()
{ 
    
    int arrChilds[5];
    int zombie;

            printf("\n");

	for(int i=0;i<5;i++) // loop will run n times (n=5) 
	{ 
		if(fork() == 0) 
		{
			printf("PID %d ready\n",getpid()); 
			arrChilds[i]=getpid();

			exit(0); 
		} 
	} 
	for(int i=0;i<5;i++) // loop will run n times (n=5) 
	wait(NULL);
	
	
	// for(int i =0;i<5;i++)   ////send signal to all the children to kill.-------------to fix!
	// {
	   
	//    signal(SIGALRM,(void (*)(int))kill_child); 
	// }
	 
	
} 