#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 

int findNumber(int* array, int number);

int main(int argc, char const *argv[]) {
    int numberToSearch = atoi(argv[1]);    
    int matrix[5][3] = {
        {0, 0, 0}, 
        {0, 0, 0}, 
        {0, numberToSearch, 0},
        {0, 0, 0}, 
        {0, 0, 0},
    };
    pid_t pid;

    for (int i = 0; i < 5; i++) {
        pid = fork();

        if (pid < 0){
            perror("Creation of a child process was unsuccessful");
            _exit(0);
        } else
            if (pid == 0) { // Child process
                int result = 0;

                for (int j = 0; j < 3; j++) {
                    result = findNumber(&matrix[i][j], numberToSearch);
                    
                    if (result == numberToSearch) {
                        printf(
                            "Number pretended = %d, at [%d][%d]\n", 
                            result, i , j
                        );
                        _exit(0);
                    } else
                        continue;
                }     
                continue;           
            }
        return 0;
    }
}

int findNumber(int* array, int number) {
    int result = 0;

    for (int i = 0; i < 3; i++) {
        if (array[i] == number) {
            result = number;
            break;
        } else
            continue;
    }
    return result;
}