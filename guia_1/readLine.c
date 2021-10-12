#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln(int fd, char *line, size_t size);

int main(int argc, char const *argv[]) {

    int line;
    char* c = (char*) calloc(100, sizeof(char));
    
    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor < 0) {
        perror("r1");
        exit(1);
    }

    line = readln(fileDescriptor, c, 80);

    printf("Bytes readed -> %d\n", line);

    free(c);
    close(fileDescriptor);
    return line;
}

ssize_t readln(int fd, char *line, size_t size) {
    int bytesReaded;
    char* target = strchr(line, '\n');

    bytesReaded = read(fd, line, strlen(target));
    if (bytesReaded < 0) {
        perror("r2");
        bytesReaded = 0; // O bytes readed 
    }
    return bytesReaded;
}
