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
    int num, matrix[c][r]; // Number to read and matrix

    if (argc == 4) {
        c = atoi(argv[1]);
        r = atoi(argv[2]);
        num = atoi(argv[3]);
    } else {
        perror("More arguments needed!");
        _exit(0);
    }

    // Initialize the matrix
    for (int i = 0; i < c; i++) 
        for (int j = 0; j < r; j++) 
            matrix[i][j] = rand() % 10;

    // Print the matrix
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }
    
    // Generate various processes, each one will read 1 line
    int total, status;
    for (int i = 0; i < c; i++) {
        
        if (!fork()) // Child process
            if (readLine(num, c, r, matrix, i))
            {
                /* code */
            }
            
        
    }  
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
        if (matrix[column][lineN] == num)
            counter++;
    return counter;    
}
