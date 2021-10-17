#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#define SPACE 1024 // Allocated memory for the String

ssize_t readln(int fd, char *line, size_t size);

int main(int argc, char const *argv[]) {

    int bytesReaded;
    char* c = (char*) calloc(SPACE, sizeof(char));
    
    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor < 0) {
        perror("r1");
        exit(1);
    }

    bytesReaded = readln(fileDescriptor, c, SPACE);

    printf("Bytes readed -> %d\n", bytesReaded);

    free(c);
    close(fileDescriptor);
    return bytesReaded;
}

ssize_t readln(int fd, char *line, size_t size) {
    char* ln = calloc(SPACE, sizeof(char));
    
    int bytesReaded = read(fd, line, size);
    if(bytesReaded < 0) {
        perror("r1");
        exit(1);
    }

    int i = 0, i1 = 0;
    int numLines = 1; // #lines
    
    while(i <strlen(line)) {
        ln[i1] = line[i];
        i1++;

        if(line[i] == '\n') {
            printf("%d: %s", numLines, ln);
            ln[0] = '\0';
            i1 = 0;
            numLines++;
        }
        i++;
    }
    free(ln);
    return bytesReaded;
}
