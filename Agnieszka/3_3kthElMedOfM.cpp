#include<iostream>
#include <time.h>
using namespace std;
inline int getRand(int l, int r){
    return l+rand()%(r-l+1);
}
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
int medOfMed (int *A, int siz){
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
int part(int A[], int left, int right, int piv){
    int i;
    for (i=left; i<right; i++)
        if (A[i] == piv)
           break;
    swap(A[i], A[right]);
    int mid=left-1;
    for(int i=left;i<=right;i++){
        if(A[i]<=piv){
            mid++;
            swap(A[i],A[mid]);
        }
    }
    return mid;
}
int findKth(int A[], int left, int right, int k){ // where first el is k=1
    int medOfmed=medOfMed(A+left, right-left+1);
    int pi=part(A, left, right, medOfmed);
    if(pi-left+1<k){
        findKth(A, pi+1, right, k-(pi+1)+left);
    }
    else if(pi-left+1>k){
        findKth(A, left, pi-1, k);
    }
    else return A[pi];
}
bool majorEl(int A[], int n){ // n - nr of el
    int cand = findKth(A, 0, n-1, n/2);
    // checking if cand is a majority el
    int cnt=0;
    for(int i=0;i<n;i++) if(A[i]==cand) cnt++;
    if((cnt+1)>n/2) return true;
    return false;
}

main(){
    srand(time(NULL));
    int t[]={7,7,5,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5,5,2};
    cout<<majorEl(t, 21);
}
