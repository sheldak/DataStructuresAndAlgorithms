#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 10;

void countingSort(int A[N], int B[N], int divisor){

    int C[N] ={};

    for(int i=0; i<N; i++)
        C[(A[i]/divisor)%N]++;

    for(int i=1; i<N; i++)
        C[i] += C[i-1];

    for(int i=N-1; i>=0; i--)
        B[--C[(A[i]/divisor)%N]] = A[i];
}

void radixSort(int A[N]){
    int B[N];

    countingSort(A, B, 1);
    countingSort(B, A, N);
}


void c2_2b(){
    srand(time(nullptr));

    int A[N];

    for(int i=0; i<N; i++) {
        A[i] = rand() % (N*N);
        cout << A[i] << " ";
    }
    cout<<endl;

    radixSort(A);

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
}