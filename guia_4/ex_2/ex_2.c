#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int fd[3], status; 
    pid_t pid, chPid;
    char* password = (char*) malloc(sizeof(char) * 100);
    char* message = "This will also be output to the file named \"saida.txt\"\n";
    
    
    fd[0] = open("/etc/passwd", O_RDONLY, 0664);
    fd[1] = open("saida.txt", O_WRONLY | O_APPEND, 0666);
    fd[2] = open("erros.txt", O_WRONLY | O_APPEND, 0666);

    // Redirect the standard file descriptors
    dup2(fd[0], 0);
    dup2(fd[1], 1);
    dup2(fd[2], 2);

    if(!(pid = fork())) { // Child process 
        read(0, password, 100);
        printf("password : %s\n", password);

        printf("I will be printed in the file \"saida.txt\"\n");
        write(fd[1], message, strlen(message));

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
