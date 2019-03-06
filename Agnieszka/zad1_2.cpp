#include<iostream>
using namespace std;
void mergenk(int *tab, int *ind ,int first, int last){
    int inda=ind[first];
    int indb=ind[last];
    int nrOfEl=ind[last+1]-ind[first];
    int i=0;
    int *temp=new int[nrOfEl];
    while(inda<ind[last] && indb<ind[last+1]){ // ind[k]=n
        if(tab[inda]<tab[indb]){
            temp[i++]=tab[inda];
            inda++;
        }
        else{
            temp[i++]=tab[indb];
            indb++;
        }
    }
    while(inda<ind[last]){
        temp[i++]=tab[inda];
        inda++;
    }
    while(indb<ind[last+1]){
        temp[i++]=tab[indb];
        indb++;
    }
    for(int j=0;j<nrOfEl;j++){
        tab[j+ind[first]]=temp[j];
    }

}
void sortnk(int *tab, int *ind, int n, int k, int first=0, int last=-1){ // ind - indeksy pierwszych elementow kolejnych k tablic num od 0 do k-1, ind[k]=n
    if(first==last) return;
    if (last=-1) last=k-1; // first i last - iteratory po ind
    int mid=(first+last)/2;
    sortnk(tab, ind, n, k, first, mid);
    sortnk(tab, ind, n, k, mid+1, last);
    mergenk(tab, ind, first, last);

}
main(){

}
