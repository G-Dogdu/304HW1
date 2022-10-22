#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, char* argv[]){
  
  int child_a, child_b;
  int fd1[2];
  int fd2[2];
  int fd3[2];
  int fd4[2];

  if(pipe(fd1) == -1){
     printf("an error occured with opening a pipe");
     fflush(stdout);
     return 1;
  }
  if(pipe(fd2) == -1){
     printf("an error occured with opening a pipe");
     fflush(stdout);
     return 1;
  }
  if(pipe(fd3) == -1){
     printf("an error occured with opening a pipe");
     fflush(stdout);
     return 1;
  }
  if(pipe(fd4) == -1){
     printf("an error occured with opening a pipe");
     fflush(stdout);
     return 1;
  }


  child_a = fork();

if (child_a == 0) {
    /* Child A code */
    close(fd1[1]);
    int y;
    read(fd1[0], &y, sizeof(int));
    close(fd1[0]);
    int result = y*getpid();
    printf("First Child Input: %d Output : %d \n", y, result);
    fflush(stdout);
    int arr[2] = {getpid(), result};
    close(fd3[0]);
    write(fd3[1], arr, sizeof(int)*2);
    close(fd3[1]);

} else {
    child_b = fork();

    if (child_b == 0) {
        /* Child B code */
    close(fd2[1]);    
    int y;
    read(fd2[0], &y, sizeof(int));
    close(fd2[0]);
    double result = (double) getpid()/y;
    printf("Second Child Input: %d Output : %f \n", y, result);
    fflush(stdout);
    double arr[2] = {getpid(), result};
    close(fd4[0]);
    write(fd4[1], arr, sizeof(double)*2);
    close(fd4[1]);

    } else {
     //Parent 
     close(fd1[0]);
     close(fd2[0]);
     int x;
     printf("Input a number : ");
     fflush(stdout);
     scanf("%d", &x);
     write(fd1[1], &x, sizeof(int));   
     close(fd1[1]);
     write(fd2[1], &x, sizeof(int));   
     close(fd2[1]);
     int child_a[2];
     double child_b[2];
     close(fd3[1]);
     read(fd3[0], child_a, sizeof(int)*2);
     close(fd3[0]);
     close(fd4[1]);
     read(fd4[0], child_b, sizeof(double)*2);
     close(fd4[0]);
     
     sleep(500);
     printf("Result : %f\n", child_a[1] + child_b[1]);
     fflush(stdout);
     kill(child_a[0],SIGTERM);
     kill(child_b[0],SIGTERM);
     
    }
}
    return 0;
}