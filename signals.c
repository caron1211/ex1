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




void sigCathcher(int sig);

int main()
{ 
    
    int arrChilds[5];
    int zombie;

    printf("\n");

	for(int i=0;i<5;i++) // 5 pid 
	{ 
		if(fork() == 0) 
		{
			printf("PID %d ready\n",getpid()); 
			exit(0); 
		} 
		arrChilds[i]=getpid();
	} 
 	for(int i=0;i<5;i++) // loop will run n times (n=5) 
 	wait(NULL);
	
	for(int i =0;i<5;i++)  
	{
	  signal(SIGINT,sigCathcher);
	  kill(getpid(), SIGINT); 
	  sleep(1);
	    
	}

	for(int i =0;i<5;i++)  
	{
	   zombie=arrChilds[i];
	   printf("Process %d is dead \n",zombie);
	  
	    
	}
} 

void sigCathcher(int sig)
{
  printf("PID %d caught one \n",getpid());
 // signal();
}

