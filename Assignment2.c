#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>
#define ARRAY_SIZE 5
int A[ARRAY_SIZE]= {2,1,4,3,5};

//First algorithm
int BruteForceMedian(int A[]){
	/*
	* Returns the median value in a given array A of n numbers
	* This is the kth element, where k = abs(n/2), if array were sorted
	*/
	
    int k = (int)ceil(ARRAY_SIZE/2.0); //Ceiling; number rounds to lower decimal, Cast to int because it returns a double
	for(int i = 0; i < ARRAY_SIZE-1; i++){
        int numsmaller = 0; // How many elements are smaller than A[i]
        int numequal = 0; // How many elements are equal to A[i]
        for(int j = 0; j < ARRAY_SIZE-1; j++){
            if(A[j] < A[i]){
                numsmaller++;
            } else if(A[j] == A[i]){
				numequal++;
            }
        }
        if( (numsmaller < k) && k <= (numsmaller + numequal) ){ // if the index of 
			return A[i];
        }
    }
}

//Prints Aray
void print_array(int array[]){
    printf("[ ");
    for(int i = 0; i < ARRAY_SIZE; ++i){
        printf("%d ", array[i]);
    }
    printf("]\n");
}

void swap(int first,int second){
    int temp = first;
    first = second;  
    second = temp;
}

int Partition(int A[],int l,int h){
	// Partitions array slice A[l..h] by moving element A[l] to the position
	// it would have if the array slice was sorted, and by moving all
	// values in the slice smaller than A[l] to earlier positions, and all values
	// larger than or equal to A[l] to later positions. Returns the index at which
	// the ‘pivot’ element formerly at location A[l] is placed.
	int pivotval = A[l]; //Choose first value in slice as pivot value
	int pivotloc = l; //location to insert pivot
	for (int j = l +1; j < h; j++){ //j = 1
		if (A[j] < pivotval){
			pivotloc = pivotloc +1;
			swap(A[pivotloc],A[j]); // Swap elements around the pivot
		}
	}
	swap(A[l],A[pivotloc]); //put pivot element in place
	return pivotloc;
}

int Select(int A[], int l, int m, int h){ 
    // Returns the value at index m in array sliceA[l..h]
    // if the slice were sorted into nondecreasing order
    int pos = Partition(A, l, h);
    if (pos == m){
        return A[pos];
    }else if (pos > m) {
		return Select(A, l, m, pos-1);
    }else if (pos < m) {
		return Select(A, pos + 1, m, h);
    }
}

//Second Algorithm
int Median(int A[]){
	// Returns the median value in a given array A of n numbers.
	if (ARRAY_SIZE == 1){
		return A[0];
	}else{
		return Select(A,0,(int)floor(ARRAY_SIZE/2.0),(ARRAY_SIZE-1.0)); // NB: The third argument is rounded down
	}
}

int main(int argc, char *argv[]) {
		
	// Sequential array:
	/*
	for(int i = 0; i < ARRAY_SIZE; ++i){
         A[i] = i+1; // Sequence of numbers
		 printf("%d ",A[i]);
    }
	*/

    // Random array:
    /*srand(time(NULL));
    for(int i = 0; i < ARRAY_SIZE; ++i){
        A[i] = rand() % (ARRAY_SIZE*10) + 1; // Random number between 0 and 1000?
    }
	*/
	
    printf("\n Array:\n");
    print_array(A);
	
	printf("\nCiel (%d/2)= %d, Floor (%d/2)= %d \n", ARRAY_SIZE,(int)ceil(ARRAY_SIZE/2.0), ARRAY_SIZE,(int)floor(ARRAY_SIZE/2.0));
    
    
	int bf_median = 0;
	int median =0;
	
    bf_median = BruteForceMedian(A);
    printf("\nCEIL_BF_MEDIAN POINT: %d\n", bf_median);
	
	median = Median(A);
	printf("\nFLOOR_MEDIAN POINT %d\n",median);


}