#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/wait.h> 

int readLine(
    int num, 
    int column, 
    int row, 
    int matrix[column][row],
    int lineN
);

int main(int argc, char const *argv[]) {
    int c, r; // #Columns and #Rows
    int num; // Number to read and matrix

    if (argc == 4) {
        c = atoi(argv[1]);
        r = atoi(argv[2]);
        num = atoi(argv[3]);
    } else {
        perror("More arguments needed!");
        _exit(0);
    }

    int matrix[c][r];

    // Initialize the matrix
    for (int i = 0; i < c; i++) 
        for (int j = 0; j < r; j++) 
            matrix[i][j] = rand() % 10;

    // Print the matrix
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) 
            printf("%d ", matrix[i][j]);
        
        putchar('\n');
    }
    putchar('\n');
    
    // Generate various processes, each one will read 1 line
    int status;
    for (int i = 0; i < c; i++) {

        if (!fork()) { // Child process
            status = readLine(num, c, r, matrix, i);

            if (status) {
                for (int j = 0; j < r; j++)
                    printf("%d ", matrix[i][j]);
               
                printf("\n");
            }
            _exit(status);
        }
                        
    } 

    // Receive all the returned and readed values by each process
    int status2;
    int total = 0;
    for (int i = 0; i < c; i++) {
        wait(&status2);

        if (WIFEXITED(status2)) // Child exited normally 
            total += WEXITSTATUS(status2);   
    }

    if (status2 > 0) 
        printf("Number %d, was found %d times\n", num, total);
    else
        printf("The number %d was not found.\n", num);
        
    return 0;
}

int readLine(
    int num, 
    int column, 
    int row, 
    int matrix[column][row],
    int lineN
) {
    int counter = 0;
    
    for (int i = 0; i < row; i++)
        if (matrix[lineN][i] == num)
            counter++;
    
    return counter;    
}
