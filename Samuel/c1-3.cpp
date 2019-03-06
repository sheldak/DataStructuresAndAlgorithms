#include <iostream>
#define size t[0]
using namespace std;
const int N=100;

struct medianHeap{
    int maxHeap[N];
    int minHeap[N];
};

int left(int i){
    return i*2;
}

int right(int i){
    return i*2+1;
}

int parent(int i){
    return i/2;
}

void heapify_max(int t[N], int i){
    int l = left(i);
    int r = right(i);

    int maxx = i;

    if(l<size && t[l] > t[maxx])
        maxx = l;
    if(r<size && t[r] > t[maxx])
        maxx = r;
    if(maxx != i) {
        swap(t[maxx], t[i]);
        heapify_max(t, maxx);
    }
}

void heapify_min(int t[N], int i){
    int l = left(i);
    int r = right(i);

    int minn = i;

    if(l<size && t[l] < t[minn])
        minn = l;
    if(r<size && t[r] < t[minn])
        minn = r;
    if(minn != i) {
        swap(t[minn], t[i]);
        heapify_min(t, minn);
    }
}

void insert_max(int t[N], int el){
    size++;
    t[size] = el;
    int i=size;

    while(i>1 && t[i] > t[parent(i)]) {
        swap(t[i], t[parent(i)]);
        i = parent(i);
    }
}

void insert_min(int t[N], int el){
    size++;
    t[size] = el;
    int i=size;

    while(i>1 && t[i] < t[parent(i)]) {
        swap(t[i], t[parent(i)]);
        i = parent(i);
    }
}

int get_max(int t[N]){
    int res = t[1];
    t[1] = t[size];
    size--;
    heapify_max(t, 1);
    return res;
}

int get_min(int t[N]){
    int res = t[1];
    t[1] = t[size];
    size--;
    heapify_min(t, 1);
    return res;
}

void insert(medianHeap &heap, int el){
    if(heap.maxHeap[0] == heap.minHeap[0]){
        if(heap.maxHeap[0] == 0){
            heap.maxHeap[1] = el;
            heap.maxHeap[0]++;
        }
        else{
            if(el >= heap.minHeap[1])
                insert_min(heap.minHeap, el);
            else
                insert_max(heap.maxHeap, el);
        }
    }
    else{
        if(heap.maxHeap[0] > heap.minHeap[0])
            insert_min(heap.minHeap, el);
        else
            insert_max(heap.maxHeap, el);

        if(heap.maxHeap[1] > heap.minHeap[1]){
            int tmp_max = get_max(heap.maxHeap);
            int tmp_min = get_min(heap.minHeap);

            insert_min(heap.minHeap, tmp_max);
            insert_max(heap.maxHeap, tmp_min);
        }
    }
}

void print_heap(medianHeap heap){

    cout<<"HEAP MAX:"<<endl;

    int c = 1;
    int ex = 2;
    for(int i=1; i<=heap.maxHeap[0]; i++){
        cout<<heap.maxHeap[i]<<" ";
        if(i>=c) {
            cout << endl;
            c += ex;
            ex*=2;
        }
    }

    cout<<endl;

    cout<<"HEAP MIN:"<<endl;

    c = 1;
    ex = 2;
    for(int i=1; i<=heap.minHeap[0]; i++){
        cout<<heap.minHeap[i]<<" ";
        if(i>=c) {
            cout << endl;
            c += ex;
            ex*=2;
        }
    }
}

float getMedian(medianHeap heap){
    if(heap.minHeap[0] == heap.maxHeap[0]) {
        float res;
        res = heap.minHeap[1] + heap.maxHeap[1];
        res /= 2.0;
        return res;
    }
    else if(heap.minHeap[0] > heap.maxHeap[0])
        return heap.minHeap[1];
    else
        return heap.maxHeap[1];
}

void c1_3(){
    medianHeap heap;
    heap.maxHeap[0] = 0;
    heap.minHeap[0] = 0;

    insert(heap, 1);
    insert(heap, 2);
    insert(heap, 3);
    insert(heap, 6);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 8);
    insert(heap, 3);

    print_heap(heap);
    cout<<endl;
    cout<<"Median: "<<getMedian(heap);
}