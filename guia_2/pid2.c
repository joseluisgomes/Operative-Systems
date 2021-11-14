#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    pid_t pid = fork(); 
    
    if (pid < 0) {
        perror("Fork failed");
        _exit(0);
    } else
        if (pid == 0)
            _exit(0); // Terminate the child process
        else
            pid = wait(NULL);
        
    printf("Child pid = %d\n", pid);
    printf("Parent pid = %d\n", getpid());
    return 0;
}
