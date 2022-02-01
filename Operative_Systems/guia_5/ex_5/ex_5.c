#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int fd[3][2];

    pipe(fd[2]);
    if (fork()) {
        pipe(fd[1]);
        
        if (fork()) {
            pipe(fd[0]);
            
            if (fork()) {
                close(fd[0][0]);
                dup2(fd[0][1], 1);

                execlp("grep", "grep", "-v" ,"^#", "/etc/passwd", NULL);
                _exit(-1);
            } else {
                wait(NULL);
                close(fd[0][1]);
                close(fd[1][0]);
                dup2(fd[0][0], 0);
                dup2(fd[1][1], 1);

                execlp("cut", "cut", "-f7", "-d:", NULL);
                _exit(-1);
            }
        } else {
            wait(NULL);
            wait(NULL);
            close(fd[1][1]);
            close(fd[2][0]);
            dup2(fd[1][0], 0);
            dup2(fd[2][1], 1);

            execlp("uniq", "uniq", NULL);
            _exit(-1);
        }      
    } else {
        wait(NULL);
        wait(NULL);
        wait(NULL); 
        close(fd[2][1]);
        dup2(fd[2][0], 0);
        close(fd[2][0]);

        execlp("wc", "wc", "-l", NULL);
        _exit(-1);
    }
    return 0;
}
