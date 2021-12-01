#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    int fd1 = open("/etc/passwd", O_RDONLY, 0664);
    int fd2 = open("saida.txt", O_WRONLY, 0666);
    int fd3 = open("erros.txt", O_WRONLY, 0666);

    if (fd1 < 0) {
        perror("saida.txt");
        close(fd1);
        _exit(0);
    }
    dup2(fd1, 0);

    char* password = (char*) malloc(sizeof(char) * 100);
    read(0, password, 100);
    printf("password : %s\n", password);

    dup2(fd2, 1);
    dup2(fd3, 2);


    printf("I will be printed in the file saida.txt\n");  
    close(fd2);

    return 0;
}
