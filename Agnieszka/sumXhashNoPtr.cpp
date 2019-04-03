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
    bool *full;
    hashArray(int);
};
hashArray::hashArray(int max_siz){
    this->max_siz=max_siz;
    siz=0;
    ar=new int[max_siz];
    del=new bool[max_siz];
    full=new bool[max_siz];
    for(int i=0;i<max_siz;i++){
        ar[i]=0;
        del[i]=full[i]=0;
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
    A.full[key+i*i]=true;
    A.ar[key+i*i]=val;
    return true;
}
int find_el(hashArray A, int val){ // returns index of the element or -1 if not found
    int key=hashFun(val,A.max_siz);
    int i=0;
    while(A.ar[key+i*i]!=val && (A.full[key+i*i] || A.del[key+i*i])){
        i++;
    }
    if(A.full[key+i*i]) return key+i*i; // el found
    return -1;
}
void delete_el(hashArray A, int val){
    int ind = find_el(A, val);
    A.ar[ind]=0; // redundant
    A.full[ind]=false;
    A.del[ind]=true;
}
int diffWays(int A[N], int x){
    int ret=0;
    hashArray h= hashArray(N);
    for(int i=0;i<N;i++){
        if(find_el(h, A[i])) continue;
        if(find_el(h, x-A[i] )>=0){
            ret++;
        }
        insert_el(h, A[i]);
    }
    return ret;
}
main(){


}
