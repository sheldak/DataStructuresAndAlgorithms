#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;    // NIE DZIALA

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

int partition_MF(int A[N], int p, int r, int s){
    int i = p-1;

    for(int j=p; j<r; j++){
        if(A[j] <= s){
            i++;
            swap(A[i], A[j]);
        }
    }
    return i;
}

int magicFives(int A[N], int p, int r){
    if(r-p < 5)
        return median(A, p ,r);

    int *B = new int[(r-p)/5 + 1];       // tablica median

   // int B[N];
    for(int i=p; i<r; i+=5)
        B[(i-p)/5] = median(A, i, min(i+4, r));

    int x = magicFives(B, 0, (r-p)/5);
    delete []B;
    return x;
}

int select(int A[N], int p, int r, int inx){
    if(p==r)
        return A[p];

    int q = partition_MF(A, p, r, magicFives(A, p, r));

    int k = q - p + 1;
    if(inx == k)
        return A[q];
    else if(inx < q)
        return select(A, p, q, inx);
    else
        return select(A, q+1, r, inx - k);
}

void c3_3a(){
    srand(time(nullptr));

    //int A[N] = {1,2,3,2,2,5,1,2,2,5};     // N = 10
    //int A[N] = {1,6,2,2,2,5,2,2,2,5};     // N = 10
    int A[N] = {5,12,5,22,2,5,1,5,2,5,5,16,1,5,5};
    //int A[N] = {5,12,5,22,2,6,1,5,2,0,5,16,1,5,5};

    for(int i=0; i<N; i++){
        //  A[i] = rand()%(N*N);
        cout<<A[i]<<" ";
    }
    cout<<endl;

    int x = select(A, 0, N-1, N/2);     // jesli jakas liiczb jest >N/2 razy to jest tez mediana

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