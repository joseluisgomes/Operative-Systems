#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h> 
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int fd[2], status; // File descriptors
    int  position, j = 0;
    pid_t chPid; // Child pid

    if (argv[1] != NULL && argv[2] != NULL) 
        if (!strcmp("-i", argv[1])) {
            position = 3;

            fd[0] = open(argv[2], O_CREAT | O_RDONLY, 0666);
            dup2(fd[0], 0);
        }           
        
    if(argv[3] != NULL && argv[4] != NULL)
        if(!strcmp("-o", argv[3])) {
            position = position == 3 ? 3 : 5;

            fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_APPEND, 0666);
            dup2(fd[1], 1);
        }

    char* args[] = {}; // Command arguments

    for (int i = position; i < argc; i++, j++)
        strcpy(args[j], argv[i]);
    args[j] = NULL;

    if (!(chPid = fork())) { // Child process
        execvp(args[0], args);
        _exit(0);
    }
    
    chPid = wait(&status);
    if (WIFEXITED(status))
        if (!WEXITSTATUS(status))
            printf("Child -> pid = %d, free.\n", chPid);
        
    return 0;
}