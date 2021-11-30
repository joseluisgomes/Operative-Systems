#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char const *argv[]) {
    pid_t pid;

    if (!(pid = fork())) { // Child process
        printf("Child pid = %d\n", getpid());

        putchar('\n');
        execlp("ls", "ls", "-l", NULL);
        perror("ls");
    }
    
    printf("Parent pid = %d\n", getppid());
    return 1; // execlp() function not executed
}
