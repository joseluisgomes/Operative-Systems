#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(int argc, char const *argv[]) {
    execlp("ls", "ls", "-l", NULL);

    perror("ls");
    return 1;
}

