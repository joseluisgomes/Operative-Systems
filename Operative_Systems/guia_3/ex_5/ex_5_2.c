#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid[argc];    
    int status;

    for (int i = 0; i < argc; i++) {
        if (!(pid[i] = fork())) { // Child process
            execlp(argv[i], argv[i], NULL);
            perror(argv[i]);

            _exit(0);
        }    
    }
    
    for (int i = 0; i < argc; i++) {
        waitpid(pid[i], &status, 0);

        if (WIFEXITED(status)) 
            if (WEXITSTATUS(status))
                printf("Child #%d , pid = %d FREE!", i + 1, pid[i]);
    }

    return 0;
}
