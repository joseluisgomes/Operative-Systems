#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h> 
#include <fcntl.h> 

int main(int argc, char const *argv[]) {
    int fd = open("C:\\Users\\User\\OneDrive\\Documents\\GitHub\\Operative-Systems\\Operative_Systems\\guia_6\\ex_1", O_WRONLY, 0666);
    char input[256];

    while (read(0, input, 256))
        write(fd, input, 256);
    
    close(fd);
    return 0;
}
