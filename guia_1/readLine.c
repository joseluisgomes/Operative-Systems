#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln(int fd, char *line, size_t size);

int main(int argc, char const *argv[]) {

    int line;
    char* c = (char*) calloc(1024, sizeof(char));
    
    int fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor < 0) {
        perror("r1");
        exit(1);
    }

    line = readln(fileDescriptor, c, 80);

    printf("\nBytes readed -> %d\n", line);

    free(c);
    close(fileDescriptor);
    return line;
}

ssize_t readln(int fd, char *line, size_t size) {
    char* ln = calloc(1024, sizeof(char));
    int result = read(fd, line, size);

    if(result < 0) {
        perror("r1");
        exit(1);
    }
    int i = 0, i1 = 0, n = 1;
    
    while(i <strlen(line)) {
        ln[i1] = line[i];
        i1++;

        if(line[i] == '\n') {
            printf("%d: %s", n, ln);
            ln[0] = '\0';
            i1 = 0;
            n++;
        }
        i++;
    }
    return result;
}
