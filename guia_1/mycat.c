#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    char* c = (char *) calloc(1024, sizeof(char));
    int bytesReaded;

    while((bytesReaded = read(0, c, sizeof(c))) > 0) 
        write(1, c, bytesReaded);
    
    free(c);
    return 0;
}
