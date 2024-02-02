#include "the3.h"
// do not add extra libraries, but you can define helper functions below.



int gappts, mmatchpts, matchpts;


/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/

int negcheck(int a){
    if(a < 0) return 1;
    return 0;
}
int comp(char a, char b) {
    if (a == b) return matchpts;
    else return -mmatchpts;
}

int recursive_H1(std::string A, std::string B, std::string &alignSTR, int i, int j, int &callcounts) {
    
    callcounts++;
    if (callcounts >= 1000000) {
        alignSTR = "STACK LIMIT REACHED";
        return INT_MIN;
    }
    if (negcheck(i) && negcheck(j)) {
            alignSTR = "";
        return 0;
    }
    if (negcheck(i)) {
            int temp = recursive_H1(A, B, alignSTR, i, j - 1, callcounts) - gappts;
            alignSTR.push_back('_');
        return temp;
    }
    if (negcheck(j)) {
            int temp = recursive_H1(A, B, alignSTR, i - 1, j, callcounts) - gappts;
            alignSTR.push_back('.');
        return temp;
    }
    
    
    std::string pos1, pos2, pos3;
    int val1 = recursive_H1(A, B, pos1, i - 1, j - 1, callcounts) + comp(A[i], B[j]);
    // if overflow
    if (pos1 == "STACK LIMIT REACHED") {
        alignSTR = pos1;
        return INT_MIN;
    }
    
    int val2 = recursive_H1(A, B, pos2, i - 1, j,callcounts) - gappts;
    if (pos2 == "STACK LIMIT REACHED") {
        alignSTR = pos2;
        return INT_MIN;
    }
    
    int val3 = recursive_H1(A, B, pos3, i, j - 1,callcounts) - gappts;
    if (pos3 == "STACK LIMIT REACHED") {
        alignSTR = pos3;
        return INT_MIN;
    }
    
    
    // if first call max
    if (val1 >= val2 && val1 >= val3) {
        // if chars matching
        if (A[i] == B[j]) pos1.push_back(A[i]);
        else pos1.push_back('!');
        alignSTR = pos1;
        return val1;
    }
    
    
    // if second call max
    else if (val2 > val1 && val2 > val3) {
        pos2.push_back('.');
        alignSTR = pos2;
        return val2;
    }
    
    
    // if third call max
    else {
        pos3.push_back('_');
        alignSTR = pos3;
        return val3;
    }
    
}



int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count){
    
    int callcounts = call_count;
    gappts = gap;
    mmatchpts = mismatch;
    matchpts = match;
    
    return recursive_H1(sequence_A, sequence_B, possible_alignment, sequence_A.size() - 1, sequence_B.size() - 1,callcounts);
}


/*PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){
    int i = 0;
    int j = 0;
    std::vector<std::vector<int>> dpTable(sequence_A.size() + 1, std::vector<int>(sequence_B.size() + 1));
    while (i <= sequence_A.size()) {
        dpTable[i][0] = i * gap * (-1);
        ++i;
    }
    while (j <= sequence_B.size()) {
        dpTable[0][j] = j * gap * (-1);
        ++j;
    }

    for (i = 1; i <= sequence_A.size(); i++) {
        for (j = 1; j <= sequence_B.size(); j++) {
            int temp1 = dpTable[i-1][j-1] + comp(sequence_A[i - 1], sequence_B[j - 1]);
            int temp2 = dpTable[i][j-1] - gap;
            int temp3 = dpTable[i-1][j] - gap;
            dpTable[i][j] = std::max({temp1,temp2, temp3 });
        }
    }
    
    std::string sqA = "";
    std::string sqB = "";
    for (i = sequence_A.size(), j = sequence_B.size(); i > 0 && j > 0;) {
        if (dpTable[i-1][j-1] + comp(sequence_A[i - 1], sequence_B[j - 1]) == dpTable[i][j] ) {
            sqA = sequence_A[--i] + sqA;
            sqB = sequence_B[--j] + sqB;
        }
        
        else if (dpTable[i-1][j] - gap == dpTable[i][j]) {
            sqA = sequence_A[--i] + sqA;
            sqB = '.' + sqB;
        }
        
        else {
            sqA = '_' + sqA;
            sqB = sequence_B[--j] + sqB;
        }
    }
    for (; j > 0; --j) {
        sqA = '_' + sqA;
        sqB = sequence_B[j - 1] + sqB;
    }
    for (; i > 0; --i) {
        sqA = sequence_A[i - 1] + sqA;
        sqB = '.' + sqB;
    }
    possible_alignment = "";
    for (int i = 0; i < sqA.size(); i++) {
        if (sqA[i] == sqB[i]) possible_alignment.push_back(sqA[i]);
        else if (sqA[i] == '_') possible_alignment.push_back('_');
        else if (sqB[i] == '.') possible_alignment.push_back('.');
        else possible_alignment.push_back('!');
    }

    return dpTable[sequence_A.size()][sequence_B.size()];
    
}








