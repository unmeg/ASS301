#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

#define NUM_EXPERIMENTS 1 

int debug = 1; // turn print statements off with 0
int ARRAY_SIZE = 4;
int brute_count = 0; 
int med_count=0;
int median_brute = 0;
int median_median = 0;
double execution_time = 0;


// Function signatures
int BruteForceMedian(int A[]);
int Median(int A[]);
int Select(int A[], int l, int m, int h);
int Partition(int A[], int l, int h);
void swap(int *first, int *second);

/*
* Returns the median value in a given array A of n numbers
* This is the kth element, where k = abs(n/2), if array were sorted
*/
int BruteForceMedian(int A[]){
    int k = (int)ceil(ARRAY_SIZE/2.0); // 9/2 = 5 so we want ceiling; cast to int because it returns a double
    for(int i = 0; i < ARRAY_SIZE; i++){
        int numsmaller = 0; // How many elements are smaller than A[i]
        int numequal = 0; // How many elements are equal to A[i]

            for(int j = 0; j < ARRAY_SIZE; j++){
                
                if(A[j] < A[i]){
                    numsmaller++;
                } else if(A[j] == A[i]){
                    numequal++;
                }

               brute_count++;
            }

            if( (numsmaller < k) && k <= (numsmaller + numequal) ){ // numsmaller is less than k and total is greater 
                return A[i];
            }

    }
}

int Median(int A[]){
    // Returns the median value in a given array of n numbers
    if(ARRAY_SIZE==1){
        return A[0];
    } else {
        return Select(A, 0, (int)floor(ARRAY_SIZE/2), ARRAY_SIZE-1);
    }
    
}

int Select(int A[], int l, int m, int h){
    // Returns the value at index m in array sliceA[l..h]
    // if the slice were sorted into nondecreasing order
    int pos = Partition(A, l, h);

    if (pos == m){ 
        return A[pos]; 
    } else if (pos > m) {
        return Select(A, l, m, pos-1); 
    } else if (pos < m) {
        return Select(A, pos + 1, m, h);
    }
    
}

// May need to be part of the function instead of a separate function
void swap(int *first, int *second) {
    int temp;

    temp = *first;
    *first = *second;  
    *second = temp;  

}

int Partition(int A[], int l, int h){
    int pivotval = A[l];
    int pivotloc = l;
    
    for(int j = l+1; j <= h; j++){ // check this -- j in l+1?
        if(A[j] < pivotval){
        pivotloc = pivotloc + 1;
            swap(&A[pivotloc], &A[j]); // swap elements around pivot
        }
        med_count++;
    }
    
    swap(&A[l], &A[pivotloc]);
    return pivotloc;
}

void print_array(int array[]){
    printf("[ ");
    for(int i = 0; i < ARRAY_SIZE; ++i){    
        printf("%d ", array[i]);
    }
    printf("]\n");
}

void run_experiment(int type){
    int A[ARRAY_SIZE];
    int B[ARRAY_SIZE];
        
    switch(type){
        case 1: // random

            srand(time(NULL));
            
            for(int i = 0; i < ARRAY_SIZE; ++i){
                int val = rand() % 1000 + 1; // Random number between 0 and 1000
                A[i] = val; 
                B[i] = val;
            }

            break;

        case 2: // ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = i + 1; // Sequence of numbers
                B[i] = i + 1;
            }

            break;
        
        case 3: // reverse-ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = ARRAY_SIZE - i; // Sequence of numbers
                B[i] = ARRAY_SIZE - i;
            }

            break;

        
    }
    
    if(debug){
        printf("Initial array: \n");
        print_array(A);
        printf("\n");
    }
    
    // pass the identical arrays to the algorithms
    median_brute = BruteForceMedian(A);
    median_median = Median(B);
  

    if(debug){
        printf("Final array (for Median()): \n");
        print_array(B);
    }
    
}

void write_to_file(char *filename, double value, int array_size){
 
    if(debug){
        printf("\nFile: %s",filename);
    }

    FILE *fp;
       
    fp=fopen(filename, "a"); //appends
    fprintf(fp, "%f,%d\n", value, array_size);
    fclose(fp);
    
    if(debug){
        printf("\n %s done\n", filename);
    }
 
}

int main(int argc, char *argv[]) {
    int A[ARRAY_SIZE];
    double average;
    int counter = NUM_EXPERIMENTS;
    int type = 1;
    char *p;
    
     if(argc != 1){
        type = strtol(argv[1], &p, 10); // takes CL input and converts to string
        ARRAY_SIZE  = strtol(argv[2], &p, 10);

        if(type > 3){
            printf("Command line argument too big.\n\n./bs <type> is the syntax.\n\n");
            exit(0);
        }
    }

    for (int experiments = 0; experiments < NUM_EXPERIMENTS; experiments++){

        if(debug){
            printf("Experiment %d..\n", experiments+1);
            counter++;
        }

        run_experiment(type);
        
    }
   

    if(debug){
        printf("\n\nBrute comps: %d\n", brute_count/NUM_EXPERIMENTS);
        printf("Partition comps: %d\n", med_count/NUM_EXPERIMENTS);
    }   
    
    printf("\nBRUTE MEDIAN: %d\n", median_brute);
    printf("MEDIAN: %d\n", median_median);

    write_to_file("brute_comps.csv",brute_count/NUM_EXPERIMENTS, ARRAY_SIZE);   
    write_to_file("median_comps.csv",med_count/NUM_EXPERIMENTS, ARRAY_SIZE);

}
