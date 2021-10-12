#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    int fileDescriptor, bytesReaded;
    char* c = (char *) calloc(100, sizeof(char));

    fileDescriptor = open(argv[1], O_RDONLY);
    if (fileDescriptor < 0) {
        perror("r1");
        exit(1);
    }

    bytesReaded = read(fileDescriptor, c, 80);
    if (bytesReaded < 0) {
        perror("r2");
        exit(1);
    }

    write(1, c, 80);
    close(fileDescriptor);
    return bytesReaded;
}
