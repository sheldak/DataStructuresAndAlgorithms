#include <iostream>
using namespace std;
const int N=10;
bool existSum(int A[N], int x ){
    int i=0,j=N-1;
    while(i<j){
        if(A[i]+A[j]<x) i++;
        else if(A[i]+A[j]>x) j--;
        else return true;
    }
    return false;
}

main(){

}
