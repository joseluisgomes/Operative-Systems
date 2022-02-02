#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <fcntl.h> 

#define SIZE 256

int main(int argc, char const *argv[]) {
    int fd;
    char* myfifo = "myfifo";
    char msg[2][SIZE];
    
    mkfifo(myfifo, 0666);
    while (1) {
        fd = open(myfifo, O_RDONLY, 0666);

        while (read(fd, msg[0], SIZE))
            write(1, msg[0], SIZE);
        close(fd);

        fd = open(myfifo, O_WRONLY, 0666);
        
        while (read(0, msg[1], SIZE))
            write(fd, msg[1], SIZE);
        close(fd);
    }

    return 0;
}
