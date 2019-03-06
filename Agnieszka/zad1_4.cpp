#include<iostream>
using namespace std;
int mergeS(int *tab,int first, int last, int mid, int inv){
    int nrOfEl=last-first+1;
    int *tmp = new int[nrOfEl];
    int indA=first, indB=mid+1;
    int i=0;
    while(indA<=mid && indB<=last){
        if(tab[indA]>tab[indB]){
            inv+=mid+1-indA;
            tmp[i++]=tab[indB++];
        }
        else{
            tmp[i++]=tab[indA++];
        }
    }
    while(indA<=mid){
        tmp[i++]=tab[indA++];
    }
    while(indB<=last){
        tmp[i++]=tab[indB++];
    }
    return inv;
}
void mergeSort(int *tab, int l, int r, int &inv){
    if(l==r) return;
    int mid=(l+r)/2;
    mergeSort(tab, l,mid, inv);
    mergeSort(tab, mid+1, r, inv);
    inv+=mergeS(tab, l,r, mid, inv);

}
main(){

}
