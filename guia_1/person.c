#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

typedef struct { char name[60]; int age; } PERSON;

int main(int argc, char const *argv[]) {
    
    int fileDescriptor = open("people.bin", O_RDWR | O_CREAT, 0664);
    char* errorMessage = NULL;
    
    if (fileDescriptor == -1 || argc != 4) {
        errorMessage = fileDescriptor == -1 ? 
            "open() failed to open the .bin file" : "Passed few arguments";
        
        perror(errorMessage);
        free(errorMessage);
        close(fileDescriptor);
    } else {
        int result;
    }
    
    return 0;
}
