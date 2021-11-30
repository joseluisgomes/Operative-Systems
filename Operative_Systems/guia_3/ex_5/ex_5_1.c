#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {   
    execvp("./ex_5_2", argv);
    perror("./ex_5_2");
    
    return 1;
}
