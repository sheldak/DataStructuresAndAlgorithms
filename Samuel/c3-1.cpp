#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 10;

int partition(int t[], int p, int r){
    int x = t[r];
    int i = p-1;

    for(int j=p; j<r; j++){
        if(t[j] < x){
            i++;
            swap(t[i], t[j]);
        }
    }
    swap(t[r], t[i+1]);
    return i+1;
}

void quickSort(int t[N], int p, int r){
    if(p<r){
        int q = partition(t, p, r);
        quickSort(t, p, q-1);
        quickSort(t, q+1, r);
    }
}

bool sum(int A[N], int x){      // lecimy z dwoch stron i sprawdzamy czy rowne x, gdy indeksy sie przetna to false
    int i=0;
    int j=N-1;

    while(i != j && A[i] + A[j] != x){
        if(A[i]+A[j] > x)
            j--;
        else
            i++;
    }

    return i != j;
}


void c3_1(){
    srand(time(nullptr));

    int A[N];

    int x = rand()%(N*N);
    cout<<x<<endl;
    cout<<endl;
    for(int i=0; i<N; i++){
        A[i] = rand()%(N*N);
        cout<<A[i]<<" ";
    }
    cout<<endl;

    quickSort(A, 0, N-1);

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";

    cout<<endl<<endl;

    if(sum(A, x))
        cout<<"YEP";
    else
        cout<<"NOPE";
}