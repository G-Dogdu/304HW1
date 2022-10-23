#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, char* argv[]) {
   

   // child prints the pid and and time in a continuous loop while parent sleeps,
   // after 5 seconds parent kills the child via kill() 

   struct timeval tv;
   time_t t;
   struct tm *info;
   gettimeofday(&tv, NULL);
   int pid = fork();   
   t = tv.tv_sec;
   
   
   if (pid == 0){
     
     while(1)
     {
     printf("The child process id is : %d\n", getpid());
     fflush(stdout);
     info = localtime(&t);
     printf("%s",asctime (info));
     fflush(stdout);
     sleep(1);
    }
   } 
   if(pid > 0){
    
    sleep(5);
    printf("The child with id : %d is killed\n", pid);
    fflush(stdout);
    kill(pid,SIGTERM);
    
   }
    
   return 0;
}
