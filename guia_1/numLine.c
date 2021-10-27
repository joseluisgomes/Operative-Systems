#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln(int fd, char *line, size_t size);

int main(int argc, char const *argv[]) {
    int fileDescriptor;
    char* c = (char*) calloc(1024, sizeof(char));

    fileDescriptor = open(argv[1], O_RDONLY, 0666);
    if (fileDescriptor < 0) {
        perror("r1");
        close(fileDescriptor);
        exit(0);
    }

    readln(fileDescriptor, c, 1024);

    free(c);
    close(fileDescriptor);
    return 0;
}

ssize_t readln(int fd, char *line, size_t size) {
    int bytesReaded, numOfLines;
    int i, j; // Counters
    char* aux = (char*) calloc(size, sizeof(char));

    numOfLines = 1;

    while ((bytesReaded = read(fd, line, size)) > 0) {
        
        for(i = 0, j = 0; *(line + i) != '\0'; i++) {
            *(aux + j) = *(line + i);
            j++;

            if(line[i] == '\n') {
                printf("%d   %s", numOfLines, aux);
                *aux = '\0';
                numOfLines++;
                j = 0;
            }
        }
    }
}

