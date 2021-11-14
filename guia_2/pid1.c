#include <stdio.h>
#include <unistd.h> 
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    printf("Child pid = %d\n", getpid());

    return 0;
}