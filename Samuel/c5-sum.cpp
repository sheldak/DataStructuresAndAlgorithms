#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 15;

struct element{
    int value;
    int index;
    bool full;
};

void print(element T[]){        // just for checking if it works
    for(int i=0; i<2*N; i++){
        if(i==0)
            cout<<"{";

        if(!T[i].full)
            cout<<"#";
        else
            cout<<T[i].value;

        if(i<=2*N-2)
            cout<<", ";
        else
            cout<<"}";
    }
    cout<<endl;
}

int hashing(int value, int it){
    return (abs(value)%(2*N) + it*it)%(2*N);
}

void insert(element T[], int v, int i){
    int it=0;
    while(T[hashing(v, it)].full)
        it++;

    T[hashing(v, it)].value = v;
    T[hashing(v, it)].index = i;
    T[hashing(v, it)].full = true;
}

int findAll(int A[], element T[], int j){
    int sum = 0;
    int it=0;
    while(T[hashing(A[j], it)].full){
        if(T[hashing(A[j], it)].value == A[j] && T[hashing(A[j], it)].index < j)
            sum++;
        it++;
    }
    return sum;
}

int sumNum(int A[N], int x){        // number of sums that x = A[i] + A[j], i<j
    element hashTab[2*N];
    int sum = 0;

    for(int i=0; i<2*N; i++)
        hashTab[i].full = false;

    for(int i=0; i<N-1; i++)        // inserting x-A[i] and then checking if exists such j that x-A[i] == A[j]
        insert(hashTab, x-A[i], i);

    print(hashTab);

    for(int j=1; j<N; j++)
        sum += findAll(A, hashTab, j);

    return sum;
}

void c5_sum(){
    srand(time(nullptr));

    int x = 2*N/3;
    int A[N];
    for(int i=0; i<N; i++)
        A[i] = rand()%(N);

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
    cout<<endl<<endl;

    cout<<sumNum(A, x);
}