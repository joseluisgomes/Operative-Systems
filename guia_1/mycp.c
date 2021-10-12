#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[])
{
    int fd1, sz; //File descriptor & size
    char* c = (char*) calloc(100, sizeof(char));

    fd1 = open("hello.txt", O_RDONLY);
    if (fd1 < 0) {
        perror("r1");
        exit(1);
    }

    sz = read(fd1, c, 30);
    int fd2 = open("hello2.txt", O_WRONLY | O_CREAT, 0644);
    if(fd2 < 0) {
        perror("r2");
        exit(1);              
    }

    int bytesWritten = write(fd2, c, sz);

    close(fd1);
    close(fd2);

    return bytesWritten;
}
