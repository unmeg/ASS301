#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

#define NUM_EXPERIMENTS 100

int debug = 1; // turn print statements off with 0
int ARRAY_SIZE = 100;
int comp_count = 0; // keep track of comps
int median = 0;

// Function signatures
int BruteForceMedian(int A[]);
void swap(int *first, int *second);

/*
* Returns the median value in a given array A of n numbers
* This is the kth element, where k = abs(n/2), if array were sorted
*/
int BruteForceMedian(int A[]){
    int k = (int)ceil(ARRAY_SIZE/2.0); 
    for(int i = 0; i < ARRAY_SIZE; i++){
        int numsmaller = 0; // How many elements are smaller than A[i]
        int numequal = 0; // How many elements are equal to A[i]

            for(int j = 0; j < ARRAY_SIZE; j++){
                
                if(A[j] < A[i]){ // This is the basic operation
                    numsmaller++;
                } else if(A[j] == A[i]){
                    numequal++;
                }

                comp_count++;
            }

            if( (numsmaller < k) && k <= (numsmaller + numequal) ){
                return A[i];
            }

    }
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
    clock_t start, finish;

    // Make a random array
    switch(type){
        case 1: // random

            srand(time(NULL));
            
            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = rand() % 1000 + 1; // Random number between 0 and 1000?
            }

            break;

        case 2: // ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = i + 1; // Sequence of numbers
            }

            break;
        
        case 3: // reverse-ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = ARRAY_SIZE - i; // Sequence of numbers
            }

            break;

        
    }
    
    if(debug){
        printf("Initial array: \n");
        print_array(A);
        printf("\n");
    }
    
    median = BruteForceMedian(A);
    
    if(debug){
        printf("Final array: \n");
        print_array(A);
    }
    
}

void write_to_file(char *filename, double value, int array_size){
 
    if(debug){
        printf("\n File: %s\n",filename);
    }

    FILE *fp;
       
    fp=fopen(filename, "a"); //appends
    fprintf(fp, "%f,%d\n", value, array_size);
    fclose(fp);
    
    if(debug){
        printf("\n %s done", filename);
    }
 
}

int main(int argc, char *argv[]) {
    int A[ARRAY_SIZE];
    double average;
    int counter = 0;
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
            printf("Experiment %d..", experiments);
            counter++;
        }

        run_experiment(type);
        
    }

    if(debug){
        printf("Comps: %d\n", comp_count/NUM_EXPERIMENTS);
        printf("MEDIAN: %d\n", median);
    }

    write_to_file("comps_brute_sorted.csv",comp_count/NUM_EXPERIMENTS, ARRAY_SIZE);   
    

}
