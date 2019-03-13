#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 10;

struct interval{
    int a;
    int b;
    int pos;
};

int partition_first(interval in[], int p, int r){
    int x = in[r].a;
    int i = p-1;

    for(int j=p; j<r; j++){
        if(in[j].a < x){
            i++;
            swap(in[i], in[j]);
        }
    }
    swap(in[r], in[i+1]);
    return i+1;
}

int partition_second(interval in[], int p, int r){
    int x = in[r].b;
    int i = p-1;

    for(int j=p; j<r; j++){
        if(in[j].b < x){
            i++;
            swap(in[i], in[j]);
        }
    }
    swap(in[r], in[i+1]);
    return i+1;
}

void quickSort_first(interval in[N], int p, int r){
    if(p<r){
        int q = partition_first(in, p, r);
        quickSort_first(in, p, q-1);
        quickSort_first(in, q+1, r);
    }
}

void quickSort_second(interval in[N], int p, int r){
    if(p<r){
        int q = partition_second(in, p, r);
        quickSort_second(in, p, q-1);
        quickSort_second(in, q+1, r);
    }
}

interval findd(interval in[N]){

    quickSort_first(in, 0, N-1);

    for(int i=0; i<N; i++)
        in[i].pos = i;

    quickSort_second(in, 0, N-1);

    int maxx = - in[0].pos;
    interval maxx_in;
    maxx_in.a = in[0].a;
    maxx_in.b = in[0].b;

    for(int i=1; i<N; i++) {
        if (i - in[i].pos > maxx){
            maxx = i - in[i].pos;
            maxx_in.a = in[i].a;
            maxx_in.b = in[i].b;
        }
    }

    return maxx_in;
}

void c2_4(){
    srand(time(nullptr));

    interval in[N];

    for(int i=0; i<N; i++){
        in[i].a = rand()%(N*N-2);
        in[i].b = in[i].a + rand()%(N*N-in[i].a+1);

        cout<<in[i].a<<" "<<in[i].b<<endl;
    }
    cout<<endl;
    interval found = findd(in);

    cout<<found.a<<" "<<found.b;
}