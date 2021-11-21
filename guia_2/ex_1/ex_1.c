#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h> 

int main(int argc, char const *argv[]) {
    
    printf("Child process: %d\n", getpid());
    printf("Parent process: %d\n", getppid());
    return 0;
}
