#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, char* argv[]){
  
  int child_a, child_b;
  int fd[2];

  if(pipe(fd) == -1){
     printf("an error occured with opening a pipe");
     fflush(stdout);
     return 1;
  }
  child_a = fork();

if (child_a == 0) {
    /* Child A code */
    close(fd[1]);
    int y;
    read(fd[0], &y, sizeof(int));
    close(fd[0]);
    printf("First Child Input: %d Output : %d \n", y, y*getpid());
    fflush(stdout);
} else {
    child_b = fork();

    if (child_b == 0) {

        /* Child B code */
    } else {
     //Parent 
     close(fd[0]);
     int x;
     printf("Input a number : ");
     scanf("%d", &x);
     write(fd[1], &x, sizeof(int));   
     close(fd[1]);
    }
}
    return 0;
}