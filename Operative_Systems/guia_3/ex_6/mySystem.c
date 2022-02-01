#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    pid_t pid;
    int status, childPid;

    if (!(pid = fork())) {
        execlp(argv[1], argv[1], NULL);
        perror(argv[1]);
    }
    
    childPid = wait(&status);
    if (WIFEXITED(status)) 
        if (!WEXITSTATUS(status))
            printf("Child -> pid = %d, free!\n", childPid);

    return 0;
}
