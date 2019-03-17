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

int magicFives(int A[N], int p, int r, int inx){    // mediana median
    if(r-p < 10){           // dla malych tablic
        quickSort(A, p ,r);
        return A[p+inx];
    }

    int *B = nullptr;       // tablica median
    B = new int[(r-p)/5 + 1];

    for(int i=p; i<r; i+=5)
        B[i/5] = median(A, i, min(i+4, r));

    int m = magicFives(B, 0, (r-p)/5, ((r-p)/5+1)/2);       // statystyczna mediana z algorytmu

    delete []B;

    int *C = nullptr;
    C = new int[r-p+1];

    int *D = nullptr;
    D = new int[r-p+1];

    int i=0;
    int j=0;
    int k=p;
    while(k<=r){        // tablice watosci mniejszych i wiekszych od m
        if(A[k] < m)
            C[i++] = A[k];
        else if(A[k] > m)
            D[j++] = A[k];

        k++;
    }

    int res = 0;
    if(i-1 >= inx)      // wiemy ktorym wyrazem z kolei jest m wiec teraz szukamy w mniejszej tablicy
        res = magicFives(C, 0, i-1, inx);
    else if(i-1 + (r-p+1)-j-i >= inx)
        res = m;
    else
        res = magicFives(D, 0, j-1, inx-(i-1 + (r-p+1)-j-i)-1);

    delete []C;
    delete []D;

    return res;
}

void c3_3(){
    srand(time(nullptr));

    //int A[N] = {1,2,3,2,2,5,1,2,2,5};     // N = 10
    //int A[N] = {1,6,2,2,2,5,2,2,2,5};     // N = 10
    int A[N] = {5,12,5,22,2,5,1,5,2,5,5,16,1,5,5};

    for(int i=0; i<N; i++){
      //  A[i] = rand()%(N*N);
        cout<<A[i]<<" ";
    }
    cout<<endl;

    int x = magicFives(A, 0, N-1, N/2);     // jesli jakas liiczb jest >N/2 razy to jest tez mediana

    int c = 0;
    for(int i=0; i<N; i++){
        if(A[i] == x)
            c++;
    }

    if(c >= N/2+1)
        cout<<"YEP";
    else
        cout<<"NOPE";

    cout<<endl;

    quickSort(A, 0, N-1);   // tylko do sprawdzenia czy dziala

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
}