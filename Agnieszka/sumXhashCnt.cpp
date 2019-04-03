#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N=1000;
struct hashArray{
    int siz;
    int max_siz;
    int *ar;
    bool *del;
    int *full;
    hashArray(int);
};
hashArray::hashArray(int nrEl){
    this->max_siz=nrEl*2;
    siz=0;
    ar=new int[max_siz];
    del=new bool[max_siz];
    full=new int[max_siz];
    for(int i=0;i<max_siz;i++){
        ar[i]=full[i]=0;
        del[i]=0;
    }
}
int hashFun(int val, int siz){
    return val%siz;
}
bool insert_el(hashArray A, int val){
    if(A.siz+1 > A.max_siz) return false; // or resize
    A.siz++;
    int key=hashFun(val,A.max_siz);
    int i=0;
    while(A.full[key+i*i] && A.ar[key+i*i]!=val){
        i++;
    }
    A.full[key+i*i]++;
    A.ar[key+i*i]=val;
    return true;
}
int find_el(hashArray A, int val){ // returns number of elements with this value
    int key=hashFun(val,A.max_siz);
    int i=0;
    while(A.ar[key+i*i]!=val && (A.full[key+i*i] || A.del[key+i*i])){
        i++;
    }
    return A.full[key+i*i];
}
void delete_el(hashArray A, int val){
    int ind = find_el(A, val);
    A.ar[ind]=0; // redundant
    A.full[ind]=0;
    A.del[ind]=true;
}
int diffWays(int A[],int N, int x){
    int ret=0;
    hashArray h= hashArray(N);
    for(int i=0;i<N;i++){
        ret+=find_el(h, x-A[i] );
        insert_el(h, A[i]);
    }
    return ret;
}
main(){
    int A[5]={1,1,3,4,5};
    cout<<diffWays(A,5, 5);

}
