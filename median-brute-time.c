#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

#define NUM_EXPERIMENTS 100 

int debug = 1; // turn print statements off with 0
int ARRAY_SIZE = 3;
int median = 0;
double execution_time = 0;

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
                if(A[j] < A[i]){
                    numsmaller++;
                } else if(A[j] == A[i]){
                    numequal++;
                }
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
    
    // Start the clock
    start = clock();

        median = BruteForceMedian(A);
    
    // Stop the clock
    finish = clock();

    execution_time = execution_time + ((double)(finish - start)) / CLOCKS_PER_SEC;

    if(debug){
        printf("Final array: \n");
        print_array(A);
        // should be a check array in here maybe
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
        printf("\n %s done\n", filename);
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
            printf("Command line argument too big.\n\n");
            exit(0);
        }
    }

    for (int experiments = 0; experiments < NUM_EXPERIMENTS; experiments++){

        if(debug){
            printf("Experiment %d..\n", experiments);
            counter++;
        }

        run_experiment(type);
        
    }

    average = execution_time / NUM_EXPERIMENTS; // gives us average execution time
   

    write_to_file("brute_times_random.csv", average, ARRAY_SIZE);

    if(debug){
        printf("\nAverage execution time after %d trials: %f seconds\n", counter, average);
    }
    
    printf("MEDIAN: %d\n", median);

}
