#include <unistd.h>

int main(int argc, char const *argv[]) {
    int fd[2];

    if (pipe(fd) < 0)
        _exit(-1);
    
    if (!fork()) {
        close(fd[1]);
        dup2(fd[0], 0);
        execlp("wc", "wc", "-l", NULL);
    } else {
        close(fd[0]);
        close(1);
        dup(fd[1]); // fd[1] is now referencing stdout
        
        execlp("ls", "ls", "/etc", NULL); 
    }
    
    return 0;
}
