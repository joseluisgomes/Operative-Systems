#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln(int fd, char *line, size_t size) {
    int bytesReaded = read(fd, line, size);

    if (bytesReaded == -1) {
        return 0;
    } else 
        return bytesReaded;
}