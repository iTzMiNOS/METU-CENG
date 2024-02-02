#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/

int cSort(std::string* inputArray, int &arraySize, int &currentIndex) {
    
    std::string *outputArray = new std::string[arraySize];
    int *countArray = new int[26]();

    int j = 0;
    int counter = 0;
    while (j < arraySize) {
        counter++;
        if (inputArray[j].size() > currentIndex) {
            countArray[inputArray[j][currentIndex] - 65]++;
        } else {
            countArray[0]++;
        }
        j++;
    }
    
    int i = 1;
    while (i < 26) {
        counter++;
        countArray[i] += countArray[i - 1];
        i++;
    }
    
    int k = arraySize - 1;
    while (k >= 0) {
        counter++;
        if (inputArray[k].size() <= currentIndex) {
            outputArray[countArray[0] - 1] = inputArray[k];
            countArray[0]--;
        } else {
            outputArray[countArray[inputArray[k][currentIndex] - 65] - 1] = inputArray[k];
            countArray[inputArray[k][currentIndex] - 65]--;
        }
        k--;
    }
    
    int m = 0;
    while (m < arraySize) {
        counter++;
        inputArray[m] = outputArray[m];
        m++;
    }

    return counter;
}

int radix_string_sort(std::string* stringArray, int arraySize, bool ascending) {
    
    int maxWordLength = 0, totalIterations = 0;
    int i = 0;
    while (i < arraySize) {
        if (stringArray[i].size() > maxWordLength) maxWordLength = stringArray[i].size();
        i++;
    }
    
    int j = (maxWordLength - 1);
    while (j >= 0) {
        totalIterations += cSort(stringArray, arraySize, j) + 1;
        j--;
    }
    
    if (!ascending) {
        int k = 0;
        while (k < arraySize / 2) {
            std::swap(stringArray[k], stringArray[arraySize - 1 - k]);
            k++;
        }
    }
    
    return totalIterations; 
}

