#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char const *argv[]) {
    int fd[3]; // File descriptors
    char* password = (char*) malloc(sizeof(char) * 100);
    char* message = "This will also be output to the file named \"saida.txt\"\n";

    fd[0] = open("/etc/passwd", O_RDONLY, 0664);
    fd[1] = open("saida.txt", O_WRONLY | O_APPEND, 0666);
    fd[2] = open("erros.txt", O_WRONLY | O_APPEND, 0666);

    dup2(fd[0], 0);
    read(0, password, 100);
    printf("password : %s\n", password);

    dup2(fd[1], 1);
    printf("I will be printed in the file \"saida.txt\"\n");
    write(fd[1], message, strlen(message));

    dup2(fd[2], 2);

    close(0);
        close(fd[0]);
    close(1);
        close(fd[1]);
    close(2);
        close(fd[2]);
    return 0;
}
