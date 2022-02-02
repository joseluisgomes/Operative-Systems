#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 

int main(int argc, char const *argv[]) {
    mkfifo("myfifo", 0666);
    int fd[2];
    char data[256];

    while (1) {
        fd[0] = open("myfifo", O_RDONLY, 0666);
        fd[1] = open("log", O_CREAT | O_WRONLY, 0666);

        while (read(fd[0], data, 256))
            write(fd[1], data, 256);
        
        close(fd[0]);
        close(fd[1]);
    }

    return 0;
}
