void fill(int* vector, int size, int value) {
    if(vector == NULL) 
        return;
    else {
        int* v = vector;    

        if (*(v + (size-1)) == 0) {
            *(v + (size-1)) = value;
        } else 
            return; // The array is filled
    }
}

int find(int* vector, int size, int value) {
    if(vector == NULL) 
        return 0;
    else {
        int* v = vector; 
        int i; // Counter
        int aux = 0; //Auxiliary variable
        
        for(i = 0; i < size; i++) {
            if (*v == value)
                aux = *v;
            v++;
        }
        return aux;
    }
}


