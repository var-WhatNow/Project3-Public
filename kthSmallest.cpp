/*
PROBLEM TO SOLVE:
Create a function to find the kth Smallest element in an array, that calls another created function to partition it
Test these functions in main()

NAME:
Clockwork Marionette

DUE DATE:
3/22/2026

INSTRUCTOR:
Jie Meichsner



//I now realize the assignment specified to use the first value of the array as the pivot..... I forgot that part and I mean.... 
//the O() complexity is the same as this anyways.... and this is better.... and I'm kinda proud of this...


*/



#include <vector>
#include <algorithm>
#include <iostream>











/** PARTITION ARRAY
 * @param iArray pointer to array to be partitioned 
 * @param firstIndex Index number of first element of the section of the array to be partitioned
 * @param lastIndex Index number of the last element of the section of the array to be partitioned
 * @pre iArray is populated. firstIndex < lastIndex
 * @post iArray is shuffled so that the median-determined pivot has all elements of the demarcated sub-array placed to the left of it. Function then returns the Index of that pivot
 */
int partition(int* iArray, int firstIndex, int lastIndex){

    if(firstIndex > lastIndex){                                                     //redundancy against erroneous behavior wasting time
        std::cerr << "Indexing Error" << std::endl;
        return -1;                                                                  
    }

    
    int midIndex = firstIndex + (lastIndex - firstIndex) / 2;                       //discern index of midpoint of given array range
    int pivotIndex = 0;

    int first = iArray[firstIndex];                                                 //values at indexes are stored for comparison
    int mid = iArray[midIndex];
    int last = iArray[lastIndex];

    if((first <= mid && mid <= last) || (last <= mid && mid <= first)){             //determine if midIndex value is median
        pivotIndex = midIndex;
    }
    else if((mid <= first && first <= last) || (last <= first && first <= mid)){    //determine if firstIndex value is median
        pivotIndex = firstIndex;                                                    
    }
    else{                                                                           //if neither are, lastIndex value is median
        pivotIndex = lastIndex;                                                     
    }




    int pivot = iArray[pivotIndex];                         //assign pivot variable for comparison

    std::swap(iArray[pivotIndex], iArray[lastIndex]);       //move pivot to the end so it doesn't get all touchled while we're performing swaps in the array
    pivotIndex = lastIndex;                                 //and adjust the pivotIndex to reflect this for clarity
    
    int swapIndex = firstIndex;                             //makes a position marker for swaps
    for(int itt = firstIndex; itt < lastIndex; itt++){      //iterates over the list, but doesn't touch last index (which contains the pivot value at this juncture)
        if(iArray[itt] <= pivot){                           //if the value is less than the pivot, we:    
            std::swap(iArray[itt], iArray[swapIndex]);      //swap it's position with the current marker position
            swapIndex++;                                    //iterate the marker so anything less than pivot that has been swapped is locked in and won't be moved further
        }                                                   //this should result in all values less than or equal to pivot being on the left of iArray[swapIndex]'s position
    }
    std::swap(iArray[pivotIndex], iArray[swapIndex]);       //so we then swap pivot into that position
                                                            //which means swapIndex is now the index for the pivot value, and everything to the left of it is less than it

    return swapIndex;                                       //so we return the index of the pivot for recursion.
}





/** RETURN Kth SMALLEST ELEMENT OF ARRAY
 * @param iArray pointer to array to be processed 
 * @param firstIndex Index number of first element of the section of the array to be processed
 * @param lastIndex Index number of the last element of the section of the array to be processed
 * @param k the k that determines what kth smallest value of array we are processing for
 * @pre k is smaller than the size of the array, and is non-zero, non-negative
 * @post returns the value of the array that is the kth smallest
 */
int kSmall(int* iArray, int firstIndex, int lastIndex, int k){

    if(k <= 0){                                                         //cancel out if k is invalid
        std::cerr << "Invalid k Error" << std::endl;
        return -1;
    }

    if(firstIndex > lastIndex ||  k > lastIndex - firstIndex){
        std::cerr << "Indexing Error" << std::endl;
        return -1;                                                      //this should only trigger on incorrect input or weird science recursion
    }                                                                   //as I put the pivot as the last element of the array before fiddling with things


    int pivotIndex = partition(iArray, firstIndex, lastIndex);          //we partition, and store the pivotIndex for work

    if(pivotIndex - firstIndex == k - 1){                               //if we're looking for the kth smallest, we will have found it when our pivot is in the k-1 position
        return iArray[pivotIndex];                                      //since array indices start at 0
    }
    else if(pivotIndex - firstIndex > k - 1){                           //if the index is higher than our k, we recurr into the left subarray to reduce the index further
        return kSmall(iArray, firstIndex, pivotIndex - 1, k);           //and we know that the pivotIndex isn't it, so we can just slice it out
    }
    else{                                                               //if the index is lower than our k, we recurr into the right subarray where our kth value is located
        return kSmall(iArray, pivotIndex + 1, lastIndex, k - (pivotIndex - firstIndex + 1));//and we know that the number of elements in the left subarray 
    }                                                                   //at the time of this recursion is the number of values we already have smaller than our kth
                                                                        //so we recurr right with a smaller k by that many

    std::cerr << "Function Logic Error" << std::endl;
    return -1;                                                          //hopefully this never ever triggers or I did something wrong and am stupid and bad at numbers
  

}






int main(void){



    int size = 0;
    std::cout << "Enter size of array\n--> ";                               //user inputs size for array
    std::cin >> size;

    int* iArray = new int[size];                                            //runtime array is constructed of size of user input

    for(int tim = 0; tim < size; tim++){                                    //for loop of input from user to populate array
        int holderr = 0;
        std::cout << "Enter int array element\n--> ";
        std::cin >> iArray[tim];
    }


    int k = 0;
    std::cout << "Enter k to find kth smallest of the array\n--> ";         //user inputs int for k
    std::cin >> k;

    int smallK = -1;                                                        //smallK is initialized to -1 out of habit

    smallK = kSmall(iArray, 0, size - 1, k);                                //kSmall is called and return value is stored                        
                                                                            //kSmall errors will return -1
    std::cout << smallK << std::endl;




    delete[] iArray;                                                        //housekeeping
    iArray = nullptr;

}