#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    pid_t pid; 

    for (int i = 0; i < 10; i++) {
        pid = fork();

        if (pid < 0) {
            perror("Creation of a child process was unsuccessful");
            _exit(0);
        } else 
            if (pid == 0) { // Child process
                printf(
                    "Child pid: %d\nParent pid = %d\n", 
                    getpid(), getppid()
                );
                continue;
            } else { // Parent process
                printf("Parent's parent pid: %d\n", getppid());
                break;
            }     
    }
    
    return 0;
}
