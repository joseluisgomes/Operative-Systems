#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    execvp("./ex_3", argv);
    perror("./ex_3");

    return 0;
}
