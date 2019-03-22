#include <iostream>
#include <iostream>
#include <ctime>
using namespace std;

const int N = 100;

struct value{   // struktura by mozna bylo trzymac w elementach kopca nie tylko wartosci ale tez info z ktorej sa listy
    int val;
    int list;
};

struct interval{
    int a;
    int b;
};

// --- KOPIEC ---


int left(int i){
    return i*2;
}

int right(int i){
    return i*2+1;
}

int parent(int i){
    return i/2;
}

struct heap{
    int size;
    value T[N]{};

    heap(){
        size = 0;
    }

    void heapify(int i);
    void insert(value el);
    value get();
};

void heap::heapify(int i){
    int l = left(i);
    int r = right(i);

    int minn = i;

    if (l <= size && T[l].val < T[minn].val)
        minn = l;
    if (r <= size && T[r].val < T[minn].val)
        minn = r;
    if (minn != i) {
        swap(T[minn], T[i]);
        heapify(minn);
    }
}

void heap::insert(value el){
    size++;
    T[size] = el;
    int i=size;

    while(i>1 && T[i].val < T[parent(i)].val) {
        swap(T[i], T[parent(i)]);
        i = parent(i);
    }
}

value heap::get(){
    value res = T[1];
    T[1] = T[size];
    size--;
    heapify(1);
    return res;
}


// --- LISTY ---

struct node{
    int val;
    node *next;
};

void add_end(node*& head, int el){  // dodawanie na koniec

    node *p;
    node *current = head;
    p = new node;
    p->next = nullptr;
    p->val = el;
    if(current != nullptr){
        while(current->next != nullptr)
            current = current->next;

        current->next = p;
    }
    else
        head = p;
}

void print(node *h){
    node *current = h;
    if(current != nullptr) {
        cout << "{" << current->val;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->val << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->val << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;
}

void insertSort(node *&h){      // sortowanie listy, tylko pomocniczo
    node *curr = h;

    while(curr != nullptr && curr->next != nullptr){
        node *p = curr->next;
        node *tmp = h;
        if(tmp->val > curr->next->val){
            curr->next = curr->next->next;
            p->next = h;
            h = p;
        }
        else{
            while(tmp->next->val < p->val)
                tmp = tmp->next;

            if(tmp->next != p){
                curr->next = curr->next->next;
                p->next = tmp->next;
                tmp->next = p;
            }
            else
                curr = curr->next;
        }
    }
}


interval find_interval(node **list, int k){     // glowna funkcja

    interval result;
    heap h;

    int maxx=0;
    for(int i=0; i<k; i++){     // dodawanie do kopca po 1 elemencie z kazdej listy
        value x;
        x.list = i;
        x.val = list[i]->val;

        if(x.val > maxx)
            maxx = x.val;

        list[i] = list[i]->next;
        h.insert(x);
    }

    int minn;

    result.b = maxx;        // result to najlepszy dotad przedzial
    result.a = 0;

    bool flag = true;
    while(flag){        // dodajemy do kopca min element z tej listy z ktorej byl zdjety element przed chwila
        value g = h.get();
        minn = g.val;

        if(list[g.list] == nullptr)     // jak dojdziemy do konca ktorejs z list to koniec
            flag = false;

        else{
            value x;
            x.list = g.list;
            x.val = list[g.list]->val;
            list[g.list] = list[g.list]->next;

            if(x.val > maxx)
                maxx = x.val;

            h.insert(x);
        }

        if(maxx - minn < result.b - result.a){
            result.b = maxx;
            result.a = minn;
        }
    }

    return result;
}

void c18_3(){

    srand(time(nullptr));

    int k = 10;
    int n = 10;
    node **list = (node**)malloc(k*sizeof(node));

    for(int i=0; i<k; i++) {
        for (int j = 0; j < n; j++)
            add_end(list[i], rand() % 100);
    }

    for(int i=0; i<k; i++)
        insertSort(list[i]);

    for(int i=0; i<k; i++)
        print(list[i]);

    interval in = find_interval(list, k);
    cout<<in.a<<" "<<in.b;
}