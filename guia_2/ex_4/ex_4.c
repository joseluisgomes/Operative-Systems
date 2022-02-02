#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    int status;
    pid_t pid;

    for (int i = 0; i < 10; i++) {
        pid = fork();

        if (!pid) { // Child process
            printf(
                "Child #%d -> pid = %d -> Child's parent pid = %d\n",
                ++i,
                getpid(),
                getppid()
            );
            _exit(++i);
        } 
        printf(
            "My pid = %d, Parent's pid = %d, process's pid = %d\n", 
            getpid(), 
            getppid(), 
            pid
        );
    }
    
    for (int i = 0; i < 10; i++) {
        pid = wait(&status);

        if (WIFEXITED(status))
            printf("Child #%d died.\n", pid);
    }
    
    return 0;
}