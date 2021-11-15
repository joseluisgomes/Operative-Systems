#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    printf("Child pid = %d\n", getpid());
    printf("Parent pid = %d\n", getppid());

    return 0;
}