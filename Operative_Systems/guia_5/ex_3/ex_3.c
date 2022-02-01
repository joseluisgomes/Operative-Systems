#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    int fds[2];
    size_t size = sizeof(char) * 256;

    if (pipe(fds) < 0)
        _exit(-1);

    if (!fork()) {
        char* argument = (char*) malloc(size);
        
        dup2(fds[0], 0); // stdin is now refering to fds[0]
        while (read(0, argument, size)); 
        close(0);
        execlp("wc", "wc", NULL);

    } else {
        char* msg = (char*) malloc(size);
        while (read(0, msg, size))
            write(fds[1], msg, size);

        close(fds[1]);
        free(msg);
    }
    
    return 0;
}
