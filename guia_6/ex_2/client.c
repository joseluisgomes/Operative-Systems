#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 

int main(int argc, char const *argv[]) {
    int fd;
    if ((fd = open("myfifo", O_WRONLY, 0666)) == -1)
        _exit(-1);

    if (argc != 1) {
        for (int i = 1; i != argc; i++)
            write(fd, argv[i], strlen(argv[i]));
        
        close(fd);
    }
    
    return 0;
}
