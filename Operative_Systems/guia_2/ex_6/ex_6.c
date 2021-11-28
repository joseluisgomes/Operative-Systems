#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int findNumber(int row, int childPid);

int main(int argc, char const *argv[]) {
    int numberToSearch = atoi(argv[1]);    
    int matrix[5][3] = {
        {0, 0, 0}, 
        {0, 0, 0}, 
        {0, numberToSearch, 0},
        {0, 0, 0}, 
        {0, 0, 0},
    };
    pid_t pid;

    for (int i = 0; i < 5; i++) { // 5 columns => 5 processes
        pid = fork();

        if (pid < 0) {
            perror("Creation of a child process was unsuccessful");
            _exit(0);
        } else
            if (pid == 0) { // Child process
                findNumber(i + 1, getpid());
                _exit(0); // Kill the child process
            }
                  
    }
    
    return 0;
}
