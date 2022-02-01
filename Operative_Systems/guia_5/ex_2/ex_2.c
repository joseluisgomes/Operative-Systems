#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int fds[2];

    if (pipe(fds) < -1) {
        perror("pipe() failed.");
        _exit(-1);
    }
    
    if (!fork()) {
        char* msg = (char*) malloc(256);
        
        while (read(fds[0], msg, 256))
            write(1, msg, 256);

        close(fds[0]);
        free(msg);
    } else {
        int fd;
        char* msg = (char*) malloc(256);
        
        if ((fd = open("gretsch.txt", O_RDONLY, 0666)) == -1)
            _exit(-1);
        while (read(fd, msg, 256))
            write(fds[1], msg, 256);
        
        free(msg);
        close(fds[1]);
    }

    return 0;
}