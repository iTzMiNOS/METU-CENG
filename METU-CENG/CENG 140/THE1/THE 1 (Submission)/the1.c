#include <stdio.h>
#include <math.h>

int returnLowestIndex(int arr[100],int k){
    int i;
    int index;
    int min = 1000000;
    for(i = 0;i<k;i++){
        if(arr[i] < min && arr[i] >= 0) {
            min = arr[i];
            index = i;
        }
    }
    return index;
}
int main(){
	int r,k,wall[100000],w[100],h[100],t[100],p[100],s[100],a[100],n[100],i,j,till,lowestIndex,numberOfAttacks;
	numberOfAttacks = 0;
	scanf(" %d",&r);
	scanf(" %d",&k);
	for(i = 0;i<=r;i++) wall[i] = 1;
	for(i = 0;i<k;i++){
		scanf(" %d %d %d %d %d %d %d",&w[i],&h[i],&t[i],&p[i],&s[i],&a[i],&n[i]);
	}
	for(i = 0;i<k;i++) numberOfAttacks += n[i];
	for(i = 0;i<numberOfAttacks+1;i++){
		lowestIndex = returnLowestIndex(t,k);
		n[lowestIndex] -= 1;
		if(n[lowestIndex] <= 0) t[lowestIndex] = -1;
		else t[lowestIndex] += a[lowestIndex];
		if(n[lowestIndex] >= 0){
			till = p[lowestIndex]+w[lowestIndex];
			if(p[lowestIndex] >= 0 && p[lowestIndex] <= r){
				if(till > r+1) till = r+1;
				for(j = p[lowestIndex];j<till;j++){
					if(h[lowestIndex] >= wall[j]) wall[j] = h[lowestIndex];
				}
			}else if(p[lowestIndex] <= 0 && till >= 0){
				if(till > r+1) till = r+1;
				for(j = 0;j<till;j++){
					if(h[lowestIndex] >= wall[j]) wall[j] = h[lowestIndex];
			}
		}
			p[lowestIndex] += (s[lowestIndex]*a[lowestIndex]);
		}
	}
	for(i = 0;i<r;i++) printf("%d ",wall[i]);
	printf("%d\n",wall[r]);
	return 0;
}