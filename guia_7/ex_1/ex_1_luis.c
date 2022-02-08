#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 

int timer, counter = 0; 

void ctrl_c_handler(int signum) {
    counter++;
    printf("\t%d s\n", timer);
}

void ctrl_slash_handler(int signum) {
    printf("#CTRL + C = %d\n", counter);
    kill(getpid(), SIGTERM); 
}

void alarm_handler(int signum) {
    timer++;
}
 
int main(int argc, char const *argv[]) {
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, ctrl_slash_handler);
    signal(SIGALRM, alarm_handler);

    while (1) {
        alarm(1);
        pause();
    }

    return 0;
}
