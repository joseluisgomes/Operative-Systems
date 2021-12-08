#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MSGSIZE 16

int main(int argc, char const *argv[]) {
    int fileDes[2], bytesReaded, status;
    pid_t pid;
    char* inBuf[] = {}; // In buffer

    dup2(0, fileDes[0]); // fileDes[0] is the new fd of the stdin 

    if (pipe(fileDes) < 0) {
        perror("pipe function failed");
        _exit(0);
    }
    
    if (!(pid = fork())) { // Child process
        close(fileDes[1]);

        if ((bytesReaded = read(fileDes[0], inBuf, sizeof(inBuf))) > 0) {
            close(fileDes[0]);
            execvp("wc", inBuf);

            perror("execvp() function failed.");
            _exit(1);
        } else 
            _exit(2);
    } else { // Parent process
        close(fileDes[0]);

        while((bytesReaded = read(0, inBuf, sizeof(inBuf))) > 0)
            write(fileDes[1], inBuf, bytesReaded);
        
        close(fileDes[1]);
        
        pid = wait(&status);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status) == 2)
                printf("\nChild -> pid = %d, free.\n", pid);
    }
    return 0;
}
