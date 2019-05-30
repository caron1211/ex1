
// C program to illustrate
// pipe system call in C
// shared by Parent and Child
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "md5.h"
#include <string.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <signal.h>
#include <sys/fcntl.h>
using namespace std;
#define MAXMSGINPUTSIZE 20
#define MAXMSGSIZEMD5 32

int pid;

string msgMD5;

char *strInput;
  char buffer_input[MAXMSGINPUTSIZE];
  char buffer_md5[MAXMSGSIZEMD5];

void signalFun(int signo);

//p1-child read & father write , p2-child write & father read

int main()
{
  

  int p1[2], p2[2]; //p2-child to father ,  p1-father to child
  int nbytes;

  if (pipe(p1) < 0)
    exit(1);

  if (pipe(p2) < 0)
    exit(1);

  if ((pid = fork()) > 0) //father
  {
    signal(SIGINT, signalFun);

    printf("plain text:");
    scanf("%s", strInput); //father get string from the user
    if (strlen(strInput) > MAXMSGINPUTSIZE)
    {
      exit(1);
    }

    write(p1[1], strInput, MAXMSGINPUTSIZE);
    close(p1[1]);
    sleep(2);

  read(p2[0], buffer_md5, MAXMSGSIZEMD5 );

  close(p2[0]);

  }

  else if (pid == 0) { // son


    if ((nbytes = read(p1[0], buffer_input, MAXMSGINPUTSIZE)) > 0) //child read
    {

      msgMD5 = md5 (strInput);
      close(p1[0]);
      write(p2[1], msgMD5.c_str(), MAXMSGSIZEMD5); 
      close(p2[1]);
      sleep(2);
      kill(getppid(), SIGINT); // send signal to father
    }
  }

  
  else
  { // fork fail
    close(p1[1]);
    exit(1);
  }
}

void signalFun(int signo)
{

  if (strlen(msgMD5.c_str()) == MAXMSGSIZEMD5)
  {
    printf("encrypted by process %d : %s", pid, msgMD5.c_str());

    kill(pid, SIGKILL);
  }
  else
  {
    exit(1);
  }
}
