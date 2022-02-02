#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    
    if (argc != 1) {
        pid_t pid[argc-2];

        for (int i = 0; i < argc - 2; i++) {
            pid[i] = fork();

            if (!pid[i]) 
                execlp("grep", "grep", argv[1], argv[i+2], NULL);
        }

        for (int i = 0; i < argc - 2; i++) 
            kill(pid[i], SIGKILL);    
    } else
        printf("Need at least 2 arguments!");
    
    return 0;
}
