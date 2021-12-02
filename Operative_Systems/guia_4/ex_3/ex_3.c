#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <fcntl.h> 

int main(int argc, char const *argv[]) {
    int fd[3], status; // File descriptors
    pid_t chPid; // Child pid
    
    fd[0] = open("/etc/passwd", O_RDONLY, 0664);
    fd[1] = open("saida.txt", O_WRONLY | O_APPEND, 0666);
    fd[2] = open("erros.txt", O_WRONLY | O_APPEND, 0666);

    // Redirect the standard file descriptors
    dup2(fd[0], 0);
    dup2(fd[1], 1);
    dup2(fd[2], 2);

    if (!(chPid = fork())) {
        execlp(argv[1], argv[1], NULL);
        _exit(0);
    }
    
    chPid = wait(&status);
    if (WIFEXITED(status)) 
        if (!WEXITSTATUS(status))
            printf("Child -> pid = %d, free.\n", chPid);
        
    close(0);
        close(fd[0]);
    close(1);
        close(fd[1]);
    close(2);
        close(fd[2]);
    return 0;
}
