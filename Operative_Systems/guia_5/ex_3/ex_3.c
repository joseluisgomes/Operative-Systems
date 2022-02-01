#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    int fds[2];

    if (pipe(fds) < 0)
        _exit(-1);

    if (!fork()) {
        char* msg = (char*) malloc(256);

        while (read(fds[0], msg, 256))
            write(1, msg, 256);
        
        close(fds[0]);
        free(msg);
    } else {
        char* msg = (char*) malloc(256);
        
        while (read(0, msg, 256))
            write(fds[1], msg, 256);
        
        close(fds[1]);
        free(msg);
    }
    
    return 0;
}
