#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 6;

void merge(int t[N], int start, int m, int stop, int *inv) {
    int tp[N];
    int i = start;
    int j = m + 1;
    int k = 0;

    while (i <= m && j <= stop) {
        if (t[i] <= t[j])
            tp[k++] = t[i++];
        else{
            tp[k++] = t[j++];
            *inv += m-i+1;
        }
    }

    while (i <= m)
        tp[k++] = t[i++];

    while (j <= stop)
        tp[k++] = t[j++];

    for (int l = start; l <= stop; l++)
        t[l] = tp[l-start];
}

void mergeSort(int t[N], int start, int stop, int *inv){
    int m;
    if(start != stop){
        m = (start+stop)/2;
        mergeSort(t, start, m, inv);
        mergeSort(t, m+1, stop, inv);
        merge(t, start, m, stop, inv);
    }
}

void c1_4(){
    srand(time(nullptr));

    int t[N];

    for(int i=0; i<N; i++){
        t[i] = rand()%100;
        cout<<t[i]<<" ";
    }
    cout<<endl;

    int res = 0;
    int *ress = &res;

    mergeSort(t, 0, N-1, ress);

    for(int i=0; i<N; i++)
        cout<<t[i]<<" ";

    cout<<endl;
    cout<<res;
}
