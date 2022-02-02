#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

const char* msg = "Hello World!";

int main(int argc, char const *argv[]) {
    int fds[2];
    size_t msg_length = strlen(msg);

    if (pipe(fds) < -1) {
        perror("pipe() failed.");
        _exit(-1);
    }
    
    if (!fork()) {
        char* msg = (char*) malloc(msg_length);
        read(fds[0], msg, msg_length);
        write(1, msg, msg_length);

        close(fds[0]);
        free(msg);
    } else {
        sleep(5);
        write(fds[1], msg, msg_length);
        close(fds[1]);
    }

    return 0;
}
