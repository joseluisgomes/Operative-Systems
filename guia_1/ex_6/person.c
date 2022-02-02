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
int updatedPersonAge(int fd, PERSON* p, size_t cnt);

int main(int argc, char const *argv[]) {
    
    int fileDescriptor = open("people.bin", O_RDWR | O_CREAT | O_APPEND, 0664);
    char* errorMessage = NULL;
    
    if (fileDescriptor == -1 || argc != 4) {
        errorMessage = fileDescriptor == -1 ? 
            "open() failed to open the .bin file" : "Passed few arguments";
        
        perror(errorMessage);
        free(errorMessage);
        close(fileDescriptor);
    } else {
        PERSON* person = (PERSON*) malloc(sizeof(PERSON));
                person -> name = argv[2];
                person -> age = atoi(argv[3]);

        switch (*(argv[1] + 1)) {
            case 'i':
                insertNewPerson(fileDescriptor, person, sizeof(PERSON));
                break;
            case 'u':
                updatedPersonAge(fileDescriptor, person, sizeof(PERSON));
                break;
            default: 
                perror("Unknown command");
        }
        free(person);
    }
    close(fileDescriptor);
    return 0;
}

ssize_t insertNewPerson(int fd, PERSON* p, size_t cnt) {

    if(p == NULL) 
        return 0;
    else {
        char* line = (char*) calloc(1024, sizeof(char));
        
        if (readln(fd, line, 1024) > 0) 
            lseek(fd, cnt, SEEK_SET);
        
        free(line);
        return write(fd, p, cnt);
    }
}

int updatedPersonAge(int fd, PERSON* p, size_t cnt) {
    
    if (p == NULL)
        return 0;
    else {
        PERSON* aux = (PERSON*) malloc(sizeof(PERSON));

        while (read(fd, aux, sizeof(PERSON)) > 0) {
            
            if (strcmp(p -> name, aux -> name) == 0) {
                aux -> age = p -> age;
                
                lseek(fd, -sizeof(PERSON), SEEK_CUR);
                write(fd, aux, sizeof(PERSON));
                break;
            }
        }
        free(aux);
        return p -> age;
    }
}