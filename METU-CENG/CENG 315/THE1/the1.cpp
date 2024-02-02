#include "the1.h"

int cSwaps = 0;
int n_calls = 1;
int tempDistance;
double sumDist = 0;
double avgDist = 0;
double maxDist = 0;

void takeCareOfDistance(int i, int j){ //distance incrementer
    if((j - i) < 0){
        tempDistance = i - j;
    }else tempDistance = j - i;
    sumDist += tempDistance;
    if(tempDistance > maxDist){
        maxDist = tempDistance;
    }
}

void swapF(unsigned short* item1, unsigned short* item2){ //custom swap
    unsigned short temp;
    temp = *item1;
    *item1 = *item2;
    *item2 = temp;
    cSwaps++;
}

int cPart(unsigned short* arr, int size){ //classic partition
    
    unsigned short tempLast = arr[size - 1];
    int i = -1;
    for(int j = 0; j < size - 1; j++){
        if(arr[j] >= tempLast){
            i++;
            swapF(&arr[i],&arr[j]);
            takeCareOfDistance(i,j);
        }
    }
    swapF(&arr[i + 1],&arr[size - 1]);
    takeCareOfDistance(i + 1,size - 1);
    return i + 1;
}

int hPart(unsigned short* arr, int size){ //hoare partition
    
    unsigned short tempHoare = arr[(size-1)/2];
    int i = -1;
    int j = size;
    while(1){
        do  j--; while (arr[j] < tempHoare);
        do  i++; while (arr[i] > tempHoare);
        if(i < j){
            swapF(&arr[i],&arr[j]);
            takeCareOfDistance(i,j);
        }else return j;
    }
}

int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size){
    if(!hoare){ //classic
        if(!median_of_3){ //classic without median
            if(size > 1){
                int pivot = cPart(arr, size);
                quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, pivot);n_calls++;
                quickSort(&arr[pivot + 1], swap, avg_dist, max_dist, hoare, median_of_3, size - pivot - 1);n_calls++;
            }
        }else{ //classic with median
            if(size > 1){
                unsigned short* tempMedian;
                if((arr[0] < arr[size-1] && arr[0] > arr[(size-1)/2]) || (arr[0] > arr[size-1] && arr[0] < arr[(size-1)/2])){
                    swapF(&arr[size-1],&arr[0]);
                    takeCareOfDistance(size-1,0);
                }else if((arr[(size-1)/2] > arr[0] && arr[size-1] > arr[(size-1)/2]) || (arr[(size-1)/2] < arr[0] && arr[size-1] < arr[(size-1)/2])){
                    swapF(&arr[size-1],&arr[(size-1)/2]);
                    takeCareOfDistance((size-1)/2,size-1);
                }
                int pivot = cPart(arr, size);
                quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, pivot);n_calls++;
                quickSort(&arr[pivot + 1], swap, avg_dist, max_dist, hoare, median_of_3, size - pivot - 1);n_calls++;
            }
        }
    }else{ //hoare
        if(!median_of_3){ //hoare without median
            if(size > 1){
                int pivot = hPart(arr, size);
                quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, pivot + 1);n_calls++;
                quickSort(&arr[pivot + 1], swap, avg_dist, max_dist, hoare, median_of_3, size - pivot - 1);n_calls++;
            }
        }else{ //hoare with median
            if(size > 1){
                unsigned short* tempMedian;
                if((arr[0] < arr[size-1] && arr[0] > arr[(size-1)/2]) || (arr[0] > arr[size-1] && arr[0] < arr[(size-1)/2])){
                    swapF(&arr[(size-1)/2],&arr[0]);
                    takeCareOfDistance((size-1)/2,0);
                }else if((arr[size-1] < arr[0] && arr[size-1] > arr[(size-1)/2]) || (arr[size-1] > arr[0] && arr[size-1] < arr[(size-1)/2])){
                    swapF(&arr[(size-1)/2],&arr[size-1]);
                    takeCareOfDistance((size-1)/2,size-1);
                }
                int pivot = hPart(arr, size);
                quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, pivot + 1);n_calls++;
                quickSort(&arr[pivot + 1], swap, avg_dist, max_dist, hoare, median_of_3, size - pivot - 1);n_calls++;
            }
        }
    }
    swap = cSwaps;
    max_dist = maxDist;
    avg_dist = sumDist / cSwaps;;
	return n_calls;
}
