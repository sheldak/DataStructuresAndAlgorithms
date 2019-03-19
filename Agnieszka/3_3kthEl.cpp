#include<iostream>
#include <time.h>
using namespace std;
inline int getRand(int l, int r){
    return l+rand()%(r-l+1);
}

int part(int A[], int left, int right){
    int piv=getRand(left,right); // choosing random index
    cout<<piv<<" piv\n";
    swap(A[piv], A[right]); // pivot is now the last el
    piv= A[right]; // extracting value of pivot
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
    int pi=part(A, left, right);
    cout<<pi<<endl;
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
