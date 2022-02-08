#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 

#define SIZE 256

int main(int argc, char const *argv[]) {
    int fd[2][2], status; // Descriptors
    char data[SIZE];
    pid_t pid[2];

    for (int i = 0; i < 2; i++) {
        pipe(fd[i]);
        pid[i] = fork();

        if (pid[i] == 0) {
            while (read(0, data, SIZE))
                write(fd[i][1], data, SIZE);
            
            char file[5] = {data[0], '.', 'g', 'z', '\0'}; 

            dup2(fd[i][0], 0);

            int fileD = open(file, O_WRONLY, 0666);
            
            dup2(fileD, 1);
            close(fd[i][0]);
            close(fd[i][1]);
            close(fileD);

            execlp("gzip", "gzip", NULL);
            _exit(-1);
        }
    }

    for (int i = 0; i < 2; i++) {
        wait(&status);
        if (WIFEXITED(status))
            if (WEXITSTATUS(status) != -1) // Child terminated normally 
                write(1, "Child free", strlen("Child free"));  
    }
    return 0;
}
