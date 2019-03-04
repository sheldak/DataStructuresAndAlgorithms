#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
using namespace std;

const int N = 10000;

#define size t[0]


void insertSort(int t[N]){
    for(int i=1; i<N; i++){
        int x = t[i];
        int curr = i-1;
        while(curr >= 0 && t[curr] > x){
            t[curr+1] = t[curr];
            curr--;
        }
        t[curr+1] = x;
    }
}

void selectionSort(int t[N]){
    for(int i=0; i<N-1; i++){
        int minn=i;
        for(int j=i+1; j<N; j++){
            if(t[j]<t[minn])
                minn = j;
        }
        swap(t[i], t[minn]);
    }
}

void bubbleSort(int t[N]){
    for(int i=N-1; i>=1; i--){
        for(int j=0; j<i; j++){
            if(t[j]>t[j+1])
                swap(t[j], t[j+1]);
        }
    }
}

void quickSort(int t[N], int left, int right){
    int i = left;
    int j = right;
    int x = t[(left + right)/2];
    do
    {
        while(t[i]<x)
            i++;

        while(t[j]>x)
            j--;

        if(i <= j)
        {
            swap(t[i], t[j]);

            i++;
            j--;
        }
    } while(i<=j);

    if(left < j)
        quickSort(t, left, j);

    if(right > i)
        quickSort(t, i, right);
}

void combSort(int t[N]){
    int top, gap;
    bool swapped = true;

    gap = N;

    while(gap>1 || swapped){
        gap = max(int(gap/1.3), 1);
        top = N-gap;
        swapped = false;
        for(int i=1; i<top; i++){
            int j=i+gap;
            if(t[i]>t[j]){
                swap(t[i], t[j]);
                swapped = true;
            }
        }
    }
}

int left(int i){
    return i*2;
}

int right(int i){
    return i*2+1;
}

int parent(int i){
    return i/2;
}

void heapify(int t[N], int i){
    int l = left(i);
    int r = right(i);

    int maxx = i;

    if(l<size && t[l] > t[maxx])
        maxx = l;
    if(r<size && t[r] > t[maxx])
        maxx = r;
    if(maxx != i) {
        swap(t[maxx], t[i]);
        heapify(t, maxx);
    }
}

void build(int t[N]){
    for(int i=size/2; i>0; i--)
        heapify(t, i);
}

void heapSort(int t[N]){
    build(t);
    for(int i=size; i>1; i--){
        swap(t[1], t[i]);
        size--;
        heapify(t, 1);
    }
}

void sort() {

    srand(time(nullptr));
    int t[N];
    int s[N];
    t[0] = N-1;

    cout<<"Array: "<<t[0]<<" ";
    for (int i=1; i<N; i++){    // randomization
        t[i] = rand() % 10000;
        cout << t[i] << " ";
        s[i] = t[i];
    }
    cout<<endl<<endl;


    // --- QUICK SORT ---
    auto a = chrono::steady_clock::now();
    quickSort(t, 1, N-1);
    auto b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"quick sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl<<endl;


    for(int i=1; i<N; i++)
        t[i] = s[i];


    // --- COMB SORT ---
    a = chrono::steady_clock::now();
    combSort(t);
    b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"comb sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl<<endl;


    // --- HEAP SORT ---
    for(int i=1; i<N; i++)
        t[i] = s[i];

    a = chrono::steady_clock::now();
    heapSort(t);
    b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"heap sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl<<endl;


    // --- INSERT SORT ---
    for(int i=1; i<N; i++)
        t[i] = s[i];

    a = chrono::steady_clock::now();
    insertSort(t);
    b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"insert sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl<<endl;


    // --- SELECTION SORT ---
    for(int i=1; i<N; i++)
        t[i] = s[i];

    a = chrono::steady_clock::now();
    selectionSort(t);
    b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"selection sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl<<endl;


    // --- BUBBLE SORT ---
    for(int i=1; i<N; i++)
        t[i] = s[i];

    a = chrono::steady_clock::now();
    bubbleSort(t);
    b = chrono::steady_clock::now();

    cout<<t[0]<<" ";
    for (int i=1; i<N; i++)
        cout << t[i] << " ";
    cout<<endl;
    cout<<"bubble sort: "<<chrono::duration_cast<chrono::nanoseconds>(b-a).count()<<endl;
}