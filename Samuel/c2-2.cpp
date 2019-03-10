#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 10;

void countingSort(int A[N]){
    int B[N];
    int C[N*N];

    for(int i=0; i<N*N; i++)
        C[i] = 0;

    for(int i=0; i<N; i++)
        C[A[i]]++;

    for(int i=1; i<N*N; i++)
        C[i] += C[i-1];

    for(int i=N-1; i>=0; i--){
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }

    for(int i=0; i<N; i++)
        A[i] = B[i];
}

void c2_2(){
    srand(time(nullptr));

    int A[N];

    for(int i=0; i<N; i++) {
        A[i] = rand() % (N*N);
        cout << A[i] << " ";
    }
    cout<<endl;

    countingSort(A);

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
}