#include<iostream>
using namespace std;

bool majorEl(int A[], int n){ // n - nr of el
    int cnt=1;
    int maxInd=0;
    for(int i=1;i<n;i++){
        if(A[maxInd]!=A[i]) cnt--;
        else cnt++;
        if(cnt==0){
            cnt=1;
            maxInd=i;
        }
    }
    // -----checking if candidate is a majority el
    int cand=A[maxInd];
    cnt=0;
    for(int i=0;i<n;i++){
        if(A[i]==cand) cnt++;
    }
    if((cnt+1)>n/2) return true;
    return false;
}

main(){
    int t[]={7,7,5,2,2,2,2,2,2,5,5,5,5,5,5,5,5,5,5,5,2};
    cout<<majorEl(t, 21);
}
