#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MSGSIZE 16

int main(int argc, char const *argv[]) {
    int fileDes[2], numBytes, status; 
    pid_t pid;
    char inBuf[MSGSIZE]; // In buffer
    char* msg = "Hello, World!";

    if (pipe(fileDes) < 0) {
        perror("pipe function failed");
        _exit(0);
    }
    
    if (!(pid = fork())) { // Child process 
        close(fileDes[1]);

        while ((numBytes = read(fileDes[0], inBuf, strlen(msg) + 1)) > 0) 
            printf("%s\n", inBuf);
        
        if (numBytes) {
            close(fileDes[0]);
            printf("Finished reading!\n");
        }
        _exit(1);
    } else { // Parent process
        close(fileDes[0]);

        write(fileDes[1], msg, strlen(msg) + 1);
        close(fileDes[1]);

        pid = wait(&status);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status) == 1)
                printf("Child -> pid = %d, free.\n", pid);
    }
    return 0;
}
