#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 1e5

int iter = 0;

 void catchtimer(int singaln) {
    
     printf("continue prcoccessing signal...\n");
 }

 void catchSendEnd(int singaln) {

     printf("catched %d\n", singaln);
     exit(0);
 }

 void catchSendContinue(int singaln) {

    printf("catched %d\n", singaln);
 }


 void catchIgnore(int singaln) {
    
    signal(SIGINT,SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    signal(SIGALRM, SIG_IGN);
    signal(SIGUSR1, SIG_IGN);
    signal(SIGUSR2, SIG_IGN);
 }

  void catchTime(int singaln) {

      int a = iter+100;
     for (iter; iter < a;)
     {
        printf("%d %d\n", getpid(), iter++);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGALRM, SIG_IGN);
        signal(SIGUSR2, SIG_IGN);
        usleep(DELAY);
     }
    


    signal(SIGINT,SIG_DFL);
    signal(SIGTERM, catchSendEnd);
    signal(SIGALRM, catchSendContinue);
    signal(SIGUSR1,catchtimer);

 }


int main() {

    

    signal(SIGTERM, catchSendEnd);
    signal(SIGALRM, catchSendContinue);
    signal(SIGUSR1, catchTime);
    signal(SIGUSR2, catchIgnore);

    while (1) {

        ++iter;
        printf("%d %d\n", getpid(), iter);
        usleep(DELAY);
    } 
}