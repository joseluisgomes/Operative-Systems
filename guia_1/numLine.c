#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include "readln.h"
#define SIZE 1024 

int main(int argc, char const *argv[]) {
    int fileDescriptor;
    char* line = (char*) calloc(SIZE, sizeof(char));

    fileDescriptor = open(argv[1], O_RDONLY, 0666);
    if (fileDescriptor < 0) {
        perror("r1");
        close(fileDescriptor);
        exit(0);
    }

    int bytesReaded;
    int i, j; // Counters
    int numOfLines = 1; // ASCII code for “1”
    char* aux = (char*) calloc(SIZE, sizeof(char));

    while((bytesReaded = readln(fileDescriptor, line, SIZE)) > 0) {
        
        for(i = 0, j = 0; *(line + i) != '\0'; i++) {
            *(aux + j) = *(line + i);
            j++;

            if(*(line + i) == '\n') {
                printf("%d %s", numOfLines, aux);
                *aux = '\0';
                numOfLines++;
                j = 0;
            }
        }
    }

    free(line);
    free(aux);
    close(fileDescriptor);
    return 0;
}
