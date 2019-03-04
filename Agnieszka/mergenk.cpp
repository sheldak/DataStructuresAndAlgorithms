#include<iostream>
using namespace std;

int *scal(int **tab, int k, int n, int *siz){ // siz - tablica dlugosci kolejnych k tablic
    int *ind = new int[k];
    int *res = new int[n]; // wynik
    for(int i=0;i<k;i++) ind[i]=0;
    int m=0; // iterator po n
    while(m<n){
        int minV, minI; // wartosc najmn el i nr tablicy w ktorej on sie znajduje
        bool empt=true; // flaga do zapelnienia 1 wartosci
        for(int i=0;i<k;i++){
            if(siz[i]>ind[i]) // jesli indeks nie wykracza poza tablica
            {
                if(empt || minV>tab[i][ind[i]]){
                    minV=tab[i][ind[i]];
                    minI=i;
                    empt=false;
                }
            }
        }
        res[m] = minV;
        m++;
        ind[minI]++;
    }
    return res;

}
main(){
    int k=3,n=9;
    int **tab = new int*[k];
    int *siz = new int[k];
    siz[0]=2;
    siz[1]=3;
    siz[2]=4;
    for(int i=0;i<k;i++){
        tab[i]=new int[siz[i]];
    }
    tab[0][0]=3;
    tab[0][1]=3;
    tab[1][0]=3;
    tab[1][1]=4;
    tab[1][2]=6;
    tab[2][0]=3;
    tab[2][1]=6;
    tab[2][2]=8;
    tab[2][3]=9;
    int *res =scal(tab,k,n,siz);
for(int i=0;i<n;i++) cout<<res[i]<<" ";

}
