#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

int debug = 1; // turn print statements off with 0
int ARRAY_SIZE = 9;

// Function signatures
int BruteForceMedian(int A[]);
int Median(int A[]);
int Select(int A[], int l, int m, int h);
int Partition(int A[], int l, int h);
void swap(int *first, int *second);
void sort(int A[]);
int check_median(int A[], int median, int type);

/*
* Returns the median value in a given array A of n numbers
* This is the kth element, where k = abs(n/2), if array were sorted
*/
int BruteForceMedian(int A[]){
    int k = (int)ceil(ARRAY_SIZE/2.0); // 9/2 = 5 so we want ceiling; cast to int because it returns a double
    if(debug){
        printf("Median location: %d\n", k);

    }

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
        if(debug){
            printf("Median location: %d\n", (int)floor(ARRAY_SIZE/2.0));
        }
        return Select(A, 0, (int)floor(ARRAY_SIZE/2.0), ARRAY_SIZE-1);
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

void sort(int A[]){

    int count = ARRAY_SIZE - 1; // number of pairs to be compared aka len
    int sflag = 1; // swap flag (bool)

    while(sflag == 1){
        sflag = 0;
        for (int j = 0; j <= (count-1); j++){
            if (A[j + 1] < A[j] ){
                // comp_count++; // track comparison
                swap(&A[j], &A[j+1]);

                // if(debug==1){
                //     printf("%d swapped with %d\n", A[j], A[j+1]);
                //     print_array(A);
                // }
                
                sflag = 1;
            }
        }
    count--;    
    }

}

int check_median(int A[], int median, int type){
    int result = 0;
    sort(A);
    printf("Sorted array: ");
    print_array(A);

    int median_index = (int)floor(ARRAY_SIZE/2.0);
    if(debug){
    printf("Median index: %d\n", median_index);
    }

    if(A[median_index] == median){
        printf("Median given: %d, median found: %d\n", median, A[median_index]);
        printf("Successful sort!");
        result = 1;
    } else {
        printf("Median given: %d, median found: %d\n", median, A[median_index]);
        printf("Failure!");
        result = 0;
    }
   
    return result;
}


int main(int argc, char *argv[]) {
    int A[ARRAY_SIZE];
    int B[ARRAY_SIZE];
    double average;
    int type;
    int algo = 1; // brute:1, median:2
    char *p;
    int median = 0;
    
     if(argc != 1){
        type = strtol(argv[1], &p, 10); // takes CL input and converts to string
        ARRAY_SIZE  = strtol(argv[2], &p, 10);

        if(type > 3){
            printf("Command line argument too big.\n\n./bs <type> is the syntax.\n\n");
            exit(0);
        }
    }

    // Random array:
    srand(time(NULL));
            
    for(int i = 0; i < ARRAY_SIZE; ++i){
        int val = rand() % (ARRAY_SIZE*10) + 1;
        A[i] = val; // Random number between 0 and 1000?
        B[i] = val;
    }

    printf("Array A:\n");
    print_array(A);
    printf("Array B:\n");
    print_array(B);
    
    if(algo==1){
        median = BruteForceMedian(A);
        type=1;
        printf("MEDIAN: %d\n", median);
        check_median(B, median, type); // this checks array B (a duplicate of array A) to see if the value at the halfway point is
    } else {
        median = Median(A);
        type=2;
        printf("MEDIAN: %d\n", median);
        check_median(B, median, type); // this checks array B (a duplicate of array A) to see if the value at the halfway point is
    }
   
    
    
}
