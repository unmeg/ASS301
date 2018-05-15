#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for time
#include <math.h>
#define ARRAY_SIZE 100
//int A[ARRAY_SIZE]= {2,1,4,3,5};
int Basic_Operation_BruteForce = 0;
int Basic_Operation_EfficientForce = 0;


//First algorithm
int BruteForceMedian(int A[]){
	//Returns the median value in a given array A of n numbers
	//This is the kth element, where k = abs(n/2), if array were sorted
    int k = (int)ceil(ARRAY_SIZE/2.0); //Ceiling; number rounds to lower decimal, Cast to int because it returns a double
	for(int i = 0; i < ARRAY_SIZE-1; i++){
        int numsmaller = 0; // How many elements are smaller than A[i]
        int numequal = 0; // How many elements are equal to A[i]
        for(int j = 0; j < ARRAY_SIZE-1; j++){
            if(A[j] < A[i]){
				Basic_Operation_BruteForce++;
                numsmaller++;
            } else if(A[j] == A[i]){
				Basic_Operation_BruteForce++;
				numequal++;
            }
        }
        if( (numsmaller < k) && k <= (numsmaller + numequal) ){ // if the index of
			Basic_Operation_BruteForce++; //Not a basic operation 
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
	Basic_Operation_EfficientForce++;
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
			//Basic_Operation_EfficientForce++;
			pivotloc = pivotloc +1;
			swap(A[pivotloc],A[j]); // Swap elements around the pivot
		}
	}
	//Basic_Operation_EfficientForce++;
	swap(A[l],A[pivotloc]); //put pivot element in place
	return pivotloc;
}

int Select(int A[], int l, int m, int h){ 
    // Returns the value at index m in array sliceA[l..h]
    // if the slice were sorted into nondecreasing order
    
	int pos = Partition(A, l, h);
    if (pos == m){
		Basic_Operation_EfficientForce++;
        return A[pos];
    }else if (pos > m) {
		Basic_Operation_EfficientForce++;
		return Select(A, l, m, pos-1);
    }else if (pos < m) {
		Basic_Operation_EfficientForce++;
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
	int A[ARRAY_SIZE];
	//int A[ARRAY_SIZE]= {1,2,3,4,5};
	// Sequential array:
	
	for(int i = 0; i < ARRAY_SIZE; ++i){
         A[i] = i+1; // Sequence of numbers
		 printf("%d ",A[i]);
    }
	

    // Random array:
    //srand(time(NULL));
    //for(int i = 0; i < ARRAY_SIZE; ++i){
    //    A[i] = rand() % (ARRAY_SIZE*10) + 1; // Random number between 0 and 1000?
    //}
	
	
    printf("\n Array:\n");
    //print_array(A);
	printf("\nCiel (%d/2)= %d, Floor (%d/2)= %d \n", ARRAY_SIZE,(int)ceil(ARRAY_SIZE/2.0), ARRAY_SIZE,(int)floor(ARRAY_SIZE/2.0));
    
	
	double bf_start = clock();
	int bf_median = 0;
    
	bf_median = BruteForceMedian(A);
    printf("\nCEIL_BF_MEDIAN POINT: %d\n", bf_median);
	printf("BF_BASIC_OPERATION_COUNT: %d\n", Basic_Operation_BruteForce);
	
	double bf_finish = clock();
	double bf_execution_time = bf_execution_time + ((double) (bf_finish - bf_start))/CLOCKS_PER_SEC;
	printf("TIME BF: %f\n", bf_execution_time);
	
	
	double ef_start = clock();
	int median =0;
	
	median = Median(A);
	printf("\nFLOOR_MEDIAN POINT: %d\n",median);
	printf("BF_BASIC_OPERATION_COUNT: %d\n",Basic_Operation_EfficientForce);
	
	//conv3_dec (encoded, decoded, 3 * length, 0);
	double ef_finish = clock();
	double ef_execution_time = ef_execution_time + ((double)(ef_finish - ef_start))/CLOCKS_PER_SEC;
	printf("TIME BF: %f\n", ef_execution_time);
}