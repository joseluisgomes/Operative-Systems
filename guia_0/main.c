#include <stdio.h>
#include <stdlib.h>
#include "arrayFunctions.h"

int* createArray(int numOfeElements) {
    return (int*) calloc(numOfeElements, sizeof(int));
}

int main(int argc, char const *argv[]) {
    int integers[4] = {0, 1, 2, 3};
    int integers2[2] = {3};
    int* integers3 = createArray(6);

    printf("%d, %d, %d, %d\n", 
            find(integers, 4, 0),
            find(integers, 4, 1),
            find(integers, 4, 2),
            find(integers, 4, 3)
    );

    printf("\nBefore: %d\n", *integers2);

    fill(integers2, 2, 4);
    printf("After: {%d, %d}\n", 
            *integers2,
            *(integers2 + 1)
    );

    printf("\nBefore: %d\n", *(integers3 + 5));

    fill(integers3, 6, 1);
    printf("integers3[5] = %d\n", *(integers3 + 5));

    return 0;
}

