#include "the4.h"

// do not add extra libraries here
int divide_land(int X, int Y, bool** possible_plots){
    std::vector<std::vector<int>> DP(X+1,std::vector<int>(Y+1));
    if(X == 0||Y == 0){
        return 0;
    }
    if(possible_plots[X][Y] == 1){
        return 0;
    }
    int i,j,k,p;
    i = 1;
while (i <= X) {
    j = 1;
    while (j <= Y) {
        if (possible_plots[i][j]) {
            DP[i][j] = 0;
            j++;
            continue;
        }
        DP[i][j] = i * j;
        int t1 = (i + 1);
        k = 1;
        while (k <= t1 / 2) {
            DP[i][j] = std::min(DP[i][j], DP[i - k][j] + DP[k][j]);
            k++;
        }
        int t2 = (j + 1);
        p = 1;
        while (p <= t2 / 2) {
            DP[i][j] = std::min(DP[i][j], DP[i][j - p] + DP[i][p]);
            p++;
        }
        j++;
    }
    i++;
}

    return DP[X][Y];
}
