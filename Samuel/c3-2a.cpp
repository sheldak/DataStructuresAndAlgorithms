#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 15;

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

int median(int A[N], int p, int r){     // mediana z max 5 liczb
    for(int i=p; i<min(p+3, r); i++){
        int minn=i;
        for(int j=i+1; j<=r; j++){
            if(A[j]<A[minn])
                minn = j;
        }
        swap(A[i], A[minn]);
    }
    return A[(p+r)/2];
}

int magicFives(int A[N], int p, int r){
    if(r-p < 5)          // dla malych tablic
        return median(A, p ,r);

    int *B = nullptr;       // tablica median
    B = new int[(r-p)/5 + 1];

    for(int i=p; i<r; i+=5)
        B[i/5] = median(A, i, min(i+4, r));

    return magicFives(B, 0, (r-p)/5);
}

void c3_2a(){
    srand(time(nullptr));

    int A[N];

    for(int i=0; i<N; i++){
        A[i] = rand()%(N*N);
        cout<<A[i]<<" ";
    }
    cout<<endl;

    cout<<magicFives(A, 0, N-1);

    cout<<endl;

    quickSort(A, 0, N-1);   // tylko do sprawdzenia czy dziala

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
}