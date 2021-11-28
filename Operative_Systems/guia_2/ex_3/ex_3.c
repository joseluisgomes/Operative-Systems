#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    pid_t pid;
    int status = 0; 
    
    for (int i = 0; i < 10; i++) {
        pid = fork();
        
        if (pid < 0) {
            perror("Creation of a child process was unsuccessful");
            _exit(0);
        } else 
            if (pid == 0) { // Child process
                printf("Child process = %d\n", getpid());
                printf("Parent process = %d\n", getppid());
                printf("#%d\n", ++i);

                _exit(0); // Kill the child process
            } else { // Parent process
                pid = wait(&status);

                if (WIFEXITED(status)) 
                    printf("\nParent's child pid = %d\n", WEXITSTATUS(status));
            }
    }
    
    return 0;
}
