// William Su
// 100313513
// 03/6/19
// CSE100 - Lab 4-2

#include <iostream>

using namespace std;
//general use functions
int* create_array(int&);
void populate_array(int*, int);
void print_array(int*, int);

void insertion_sort_with_step_output(int*, int); //lab01 specific
void merge_sort(int*, int, int); //lab02 specific
void merge(int*, int, int, int); //lab02 specific
int max_subarray(int*, int, int); //lab03 specific
void max_heapify(int*, int, int); //lab04-1 specific
void min_heapify(int*, int, int); //lab04-1 specific
void heap_sort(int*, int); //lab04-1 specific
void quicksort(int*, int, int);
int qs_partition(int*, int, int); //lab04-2 specific

int main(){
	//General purpose setup
	int arraySize = 1; //will get this from first cin
	int* array = create_array(arraySize); //after this step, we will have empty array "array" of indicated size
	populate_array(array, arraySize); //after this step, array is filled with unsorted data
	
	//Lab specific calls
	quicksort(array, 0, arraySize - 1);
	
	//General purpose output
	print_array(array, arraySize);
	return 0;
	
}

//from lab04-2
void quicksort(int* array_data, int bot, int top){
	if(bot < top){
		int pivot  = qs_partition(array_data, bot, top);
		quicksort(array_data, bot, pivot-1);
		quicksort(array_data, pivot+1, top);
	}
}

//from lab04-2
int qs_partition(int* array_data, int bot, int top){
	int range = top - bot + 1;
	int pivotloc = rand() % range + bot;
	//move pivot to top and set pivot address
	int temp = array_data[pivotloc];
	array_data[pivotloc] = array_data[top];
	array_data[top] = temp;
	pivotloc = top;
	//swapping tool
	int cursor = bot;
	for(int i = bot; i < top; i++){
		if(array_data[i] <= array_data[pivotloc]){
			temp = array_data[cursor];
			array_data[cursor] = array_data[i];
			array_data[i] = temp;
			cursor++;
		}
	}
	temp = array_data[cursor];
	array_data[cursor] = array_data[pivotloc];
	array_data[pivotloc] = temp;
	return cursor;
}

//from lab04-1
void max_heapify(int* array_data, int parent_index, int size){
	int left_child = 2*parent_index + 1;
	int right_child = left_child + 1;
	int max = parent_index;
	if(left_child < size && array_data[left_child] > array_data[max]){
		max = left_child;
	}
	if(right_child < size && array_data[right_child] > array_data[max]){
		max = right_child;
	}
	if(max != parent_index){
		int temp = array_data[parent_index];
		array_data[parent_index] = array_data[max];
		array_data[max] = temp;
		max_heapify(array_data, max, size);
	}
}

//from lab04-1 (not used)
void min_heapify(int* array_data, int parent_index, int size){
	int left_child = 2*parent_index + 1;
	int right_child = left_child + 1;
	int min = parent_index;
	if(left_child < size && array_data[left_child] < array_data[min]){
		min = left_child;
	}
	if(right_child < size && array_data[right_child] < array_data[min]){
		min = right_child;
	}
	if(min != parent_index){
		int temp = array_data[parent_index];
		array_data[parent_index] = array_data[min];
		array_data[min] = temp;
		min_heapify(array_data, min, size);
	}
}

//from lab04-1
void heap_sort(int* array_data, int size){
	for (int i = (size/2) -1; i >= 0; i--){
		max_heapify(array_data, i, size);
	}
	for (int i = size - 1; i >= 0; i--){
		int temp = array_data[0];
		array_data[0] = array_data[i];
		array_data[i] = temp;
		max_heapify(array_data, 0, i);
	}
}	
	
//from lab03
int max_subarray(int* array_data, int left, int right){
	
	//base case, when no more recursive splitting possible
	if(left == right){
	return array_data[left];
	}
	
	//find splitting index
	int middle = left + (right - left) / 2;
	
	//recursively find max of left subarray, right subarray
	int left_max = max_subarray(array_data, left, middle);
	int right_max = max_subarray(array_data, middle + 1, right);
	
	//find max crossing subarray by moving left, then right, then combining
	//start at middle, move toward left for max
	int temp_sum = 0; //hold sum from every testing iteration
	int crossing_left = -2147483647; //set to int min value
	for (int i = middle; i >= left; i--){
		temp_sum = temp_sum + array_data[i];
		if (temp_sum > crossing_left){
			crossing_left = temp_sum;
		}
	}
	
	//start at middle, move toward right for max
	temp_sum = 0;
	int crossing_right = -2147483647;//set to int min value
	for (int i = middle + 1; i <= right; i++){
		temp_sum = temp_sum + array_data[i];
		if (temp_sum > crossing_right){
			crossing_right = temp_sum;
		}
	}
	
	//aggregate left and right max for crossing max subarray
	int crossing_max = crossing_left + crossing_right;
	
	//compare and return max result
	if(left_max >= right_max){
		if(left_max >= crossing_max){
			return left_max;
		} else {
			return crossing_max;
		}
		
	} else {
		if(right_max >= crossing_max){
			return right_max;
		} else {
			return crossing_max;
		}
	}
}

//from lab02
void merge_sort(int* array_data, int left, int right){
	
	if (left < right){
		int middle = left + (right - left) / 2;
		merge_sort(array_data, left, middle);
		merge_sort(array_data, middle+1, right);
		//start merging
		//create temp arrays
		int dim1 = middle - left + 1;
		int dim2 = right - middle;
		int lefttemp[dim1];
		int righttemp[dim2];
		
		//copy stuff over
		for(int i = 0; i < dim1; i++){
			lefttemp[i] = array_data[left + i];
		}
		for(int i = 0; i < dim2; i++){
			righttemp[i] = array_data[middle + 1 + i];
		}
		//start merging
		int i = 0;
		int j = 0;
		int k = left;
		while( i < dim1 && j < dim2){
			if(lefttemp[i] <= righttemp[j]){
				array_data[k] = lefttemp[i];
				i++;
			}
			else{
				array_data[k] = righttemp[j];
				j++;
			}
			k++;
		}
		//take care of leftover elements by iterating and inserting
		while(i < dim1){
			array_data[k] = lefttemp[i];
			i++;
			k++;
		}
		while(j < dim2){
			array_data[k] = righttemp[j];
			j++;
			k++;
		}	
			
	} 
}

//from lab01
void insertion_sort_with_step_output(int* array_data, int size){
	//holder for array content swap
	int temp = 0;

	//main insertion sort loop
	for(int count = 0; count < size; count++){

	//secondary IS loop, controls moving indicated number as far left as it should go
	//shifting loop, should always execute same number of times as count. E.G. Count = 1 (first run) this loop should run once
		for(int rover = count; rover !=0; rover--){

		//check if need to be reordered, then swap 
			if(array_data[rover] < array_data[rover-1]){
			   temp = array_data[rover];
			   array_data[rover] = array_data[rover-1];
			   array_data[rover-1] = temp;
			}//end if

		}//end for

		//display entire array in progress
		if(count != 0){
			for(int disp = 0; disp<count+1; disp++){
			cout << array_data[disp] << ";";
			}//end for
		cout << endl; //next line

		}//end if

	}//end for
	
};

//general purpose
int* create_array(int &size){
	//init vars for reading
	int* sequence; //pointer 

	//Get the size of the sequence
	cin >> size;

	//make an array of the specified size
	sequence = new int[size];
	return sequence;
}

//general purpose
void print_array(int* array_data, int size){
	for(int i = 0; i < size; i++){
		cout << array_data[i] << ";";
	}
}

//general purpose
void populate_array(int* array_data, int size){
	//Read in the sequence
	for(int i = 0; i<size; i++){
		cin >> array_data[i];
	}//end for
};

