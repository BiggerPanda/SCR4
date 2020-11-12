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

     for (int i = iter; i < iter+100; i++)
     {
        printf("%d %d\n", getpid(), i);
        signal(SIGINT,SIG_IGN);
        signal(SIGTERM, SIG_IGN);
        signal(SIGALRM, SIG_IGN);
        signal(SIGUSR1, SIG_IGN);
        signal(SIGUSR2, SIG_IGN);
        usleep(DELAY);
     }
      iter= iter+100;


    signal(SIGINT,SIG_DFL);
    signal(SIGTERM, catchSendEnd);
    signal(SIGALRM, catchSendContinue);
    signal(SIGUSR1, catchTime);
    signal(SIGUSR2, catchIgnore);

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