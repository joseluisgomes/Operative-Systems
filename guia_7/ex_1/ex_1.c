#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h> 

int ctrl_c_counter = 0; 
int timer = 0;

void ctrl_c_handler(int signum) {
    ctrl_c_counter++;
    printf("\t%d seconds\n", timer);
}

void ctrl_slash_handler(int signum) { // Ctrl + '\'
    printf("#CTRL + C = %d\n", ctrl_c_counter);
    kill(getpid(), SIGKILL);
}

int main(int argc, char const *argv[]) {
    signal(SIGINT, ctrl_c_handler);
    signal(SIGQUIT, ctrl_slash_handler);
    
    while (1) {
        sleep(1);
        timer++;
    }
    
    return 0;
}
