#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int fd[2];
    
    pipe(fd);
    if (fork()) {
        close(fd[0]);
        dup2(fd[1], 1);

        execlp("ls", "ls", "/etc", NULL);
        _exit(-1);
    } else {
        wait(NULL);
        close(fd[1]);
        dup2(fd[0], 0);

        execlp("wc", "wc", "-l", NULL);
        _exit(-1);
    }
    return 0;
}
