#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 5;

int partition(int t[], int p, int r){       // quicksort tylko do przygotowania tablicy
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

bool compare (int A[N*N], int a, int b){        // porownywanie takie zeby najpierw byly czesci z wiekszymi liczbami
    return A[N*a] > A[N*b] || (A[N*a] == A[N*b] && A[N*(a+1) - 1] >= A[N*(b+1)-1]);
}

int partition2(int A[N*N], int B[N], int p, int r){          // ten wazniejszy quicksort
    int x = B[r];
    int i = p-1;

    for(int j=p; j<r; j++){
        if(compare(A, B[j], x)){
            i++;
            swap(B[i], B[j]);
        }
    }
    swap(B[r], B[i+1]);
    return i+1;
}

void quickSort2(int A[N*N], int B[N], int p, int r){
    if(p<r){
        int q = partition2(A, B, p, r);
        quickSort2(A, B, p, q-1);
        quickSort2(A, B, q+1, r);

    }
}

void sortNNsequence(int A[], int n){
    int B[n];                  // kolejnosc w B to kolejnosc indeksow czesci w jakiej przepiszemy je do koncowej tablicy
    for(int i=0; i<n; i++)
        B[i] = i;

    quickSort2(A, B, 0 ,n-1);

    int C[N*N];

    for(int i=0; i<N; i++){
        for(int j=N-1; j>=0; j--){
            C[i*N+(N-1-j)] = A[B[i]*N + j];
        }
    }

    for(int i=0; i<N*N; i++)
        A[i] = C[i];

}

void c18_2(){
    srand(time(nullptr));

    int t[N*N];

    for(int i=0; i<N*N; i++) {      // tworzenie odpowiedniej tablicy
        t[i] = rand() % (N * N);
        cout<<t[i]<<" ";
    }
    cout<<endl;

    quickSort(t, 0, N*N-1);

    for(int i=0; i<N*N; i++)
        cout<<t[i]<<" ";

    cout<<endl;

    int A[N*N];
    bool k[N] = {false};

    for(int i=0; i<N; i++){
        int x = rand()%N;

        while(k[x]){
            x = rand()%N;
        }

        k[x] = true;

        for(int j=N*i; j<N*(i+1); j++)
            A[j] = t[j - N*i + N*x];
    }

    for(int i=0; i<N*N; i++)
        cout<<A[i]<<" ";

    cout<<endl;                     // az do tego miesjca

    sortNNsequence(A, N);

    cout<<endl;
    for(int i=0; i<N*N; i++)
        cout<<A[i]<<" ";

}