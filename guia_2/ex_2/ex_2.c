#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Creation of a child process was unsuccessful");
        _exit(0);
    } else {
        
        if (pid == 0) { // Child process
            printf("Child pid = %d\n", getpid());
            printf("Parent pid = %d\n", getppid()); 
            _exit(0);
        } else { // Parent process 
            printf("\nChild pid = %d\n", wait(NULL));
            printf("Parent pid = %d\n", getpid());
            printf("Parent's parent pid = %d\n", getppid());
        }   
    }
        
    return 0;
}
