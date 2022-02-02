#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln(int fd, char *line, size_t size);

int main(int argc, char const *argv[]) {

    char* c = (char*) calloc(1024, sizeof(char));
    
    int fileDescriptor = open(argv[1], O_RDONLY, 0666);
    if (fileDescriptor < 0) {
        perror("r1");
        close(fileDescriptor);
        exit(1);
    }

    readln(fileDescriptor, c, 1024);

    free(c);
    close(fileDescriptor);
    return 0;
}

ssize_t readln(int fd, char *line, size_t size) {
    int bytesReaded;

    while ((bytesReaded = read(fd, line, size)) > 0) 
        write(1, line, bytesReaded);
    
    return bytesReaded;
}
