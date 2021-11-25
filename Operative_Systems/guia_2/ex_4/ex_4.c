#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    pid_t pid;
    int status = 0;
    int i;

    for (i = 0; i < 10; i++) {

        if (pid > 0) // Parent process
            pid = fork();   
        else // Child process
            break;                
    }
    
    if (pid) // It's a parent
        for (int i = 0; i < 10; i++) {
            wait(&status);
            
            if (WIFEXITED(status)) // Child process ended successfully   
                printf(
                    "\nChild #%d terminated -> Child parent's id = %d\n", 
                    WEXITSTATUS(status), 
                    pid
                );
        }
    else  // It's a child
        printf(
            "\nChild #%d pid = %d\n Child's parent pid = %d\n", 
            i, 
            getpid(), 
            getppid()
        );

    return 0;
}