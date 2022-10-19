#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, char* argv[]){

   struct timeval tv;
   time_t t;
   struct tm *info;
   gettimeofday(&tv, NULL);
   t = tv.tv_sec;
   int pids[5];
   int counter;
   
for (counter = 0; counter < 4; ++counter) {
  if ((pids[counter] = fork()) < 0) {
    perror("fork");
    abort();
  } else if (pids[counter] == 0) {
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
}
       if(counter == 4) {
            sleep(5);
            for (int i = 0; i < 4; i++)
            {
            printf("The child with id : %d is killed\n", pids[i]);
            fflush(stdout);
            kill(pids[i],SIGKILL);
            }
        }
    return 0;
}