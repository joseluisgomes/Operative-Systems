#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include "readln.h"

typedef struct {
    const char* name; 
    int age;
} PERSON;

ssize_t insertNewPerson(int fd, PERSON* p, size_t cnt);

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
        
        if(strcmp(argv[1], "-i") == 0) {
            PERSON* person = (PERSON*) malloc(sizeof(PERSON));
            person -> name = argv[2];
            person -> age = atoi(argv[3]);

            insertNewPerson(fileDescriptor, person, sizeof(PERSON));
        } else {
            // Update the person data "-u"
        }
    }
    return 0;
}

ssize_t insertNewPerson(int fd, PERSON* p, size_t cnt) {

    PERSON* person = p;
    if(person == NULL) 
        return 0;
    else {
        char* line = (char*) calloc(1024, sizeof(char));
        
        if (readln(fd, line, 1024) > 0) 
            lseek(fd, cnt, SEEK_SET);
        
        return write(fd, person, cnt);
    }
}
