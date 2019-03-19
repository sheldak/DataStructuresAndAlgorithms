#include <iostream>
#include <algorithm>
using namespace std;
const int N=10;
int inSort(int *t, int siz){
    int ind=1;
    while(ind<siz){
        int j=ind-1;
        int tmp=ind;
        while(j>=0 && t[j]>t[tmp]){
            swap(t[j], t[tmp]);
            j--;tmp--;
        }
        ind++;
    }
    return t[siz/2];
}
int medOfMed (int *A, int siz=N){
    int med[(siz+4)/5];
    int i=0;
    for(; i<siz/5;i++){
        med[i]=inSort(A+i*5, 5);
    }
    if(i*5<siz){
        med[i]=inSort(A+i*5, siz-i*5);
    }
    if(i==0) return med[i];
    return medOfMed(med, (siz+4)/5);
}

main(){
    int t[]={2,2,5,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5,5,2};
    cout<<medOfMed(t,21);
}
