#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    pid_t pid;
    int status, exitval;
    status = 0;

    for (int i = 0; i < 10; i++) {
        
        if ((pid = fork()) == 0) {     
            printf("%d \n", i + 1); // #Iteration      
            printf("Child pid = %d\n", getpid());
            printf("Parent pid = %d\n", getppid());

            _exit(0);
        } else {
            
            pid = wait(&status);
            if (WIFEXITED(status)) {
                exitval = WEXITSTATUS(status);
                printf("pid = %d\n", exitval);
            }
        }
    }
    return 0;
}
