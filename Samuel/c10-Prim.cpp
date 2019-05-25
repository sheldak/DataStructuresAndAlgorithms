//  algorytm Prima z zastosowaniem kopca binarnego do znajdowania najmniejszego drzewa rozpinającego


#include <iostream>
#include <algorithm>
#define size Q[0].distance
using namespace std;

const int N = 5;

// GRAPH
struct edge{
    int vertex;
    int weight;
    edge *next;
};

void add_edge(edge **graph, int st, int nd, int weight){            // for undirected graphs
    edge *n = new edge;
    n->vertex = nd;
    n->next = nullptr;
    n->weight = weight;

    edge *curr = graph[st];
    while(curr->next != nullptr)
        curr = curr->next;

    curr->next = n;

    edge *m = new edge;
    m->vertex = st;
    m->next = nullptr;
    m->weight = weight;

    curr = graph[nd];
    while(curr->next != nullptr)
        curr = curr->next;

    curr->next = m;
}

void print(edge **graph){
    bool M[N+1][N+1];

    for(int i=0; i<N+1; i++){       // transcribing to adjacency matrix
        for(int j=0; j<N+1; j++)
            M[i][j] = false;
    }

    for(int i=0; i<N+1; i++){
        edge *curr = graph[i];
        while(curr->next != nullptr){
            M[i][curr->next->vertex] = true;
            curr = curr->next;
        }
    }

    for(int i=1; i<N+1; i++){       // printing
        for(int j=1; j<N+1; j++){
            if(M[i][j])
                cout<<1<<" ";
            else
                cout<<0<<" ";
        }
        cout<<endl;
    }
}

// PRIORITY QUEUE

struct element{
    int vertex;
    int distance;
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

void heapify(element Q[N], int *vertices, int i){
    int l = left(i);
    int r = right(i);

    int minn = i;

    if(l<size && Q[l].distance < Q[minn].distance)
        minn = l;
    if(r<size && Q[r].distance < Q[minn].distance)
        minn = r;
    if(minn != i) {
        swap(vertices[Q[minn].vertex], vertices[Q[i].vertex]);
        swap(Q[minn], Q[i]);
        heapify(Q, vertices, minn);
    }
}

void insert(element *Q, int *vertices, int vertex, int weight){
    size++;
    Q[size].vertex = vertex;
    Q[size].distance = weight;
    vertices[vertex] = size;
    int i=size;

    while(i>1 && Q[i].distance < Q[parent(i)].distance) {   // after adding new element reestablishing structure of the heap
        swap(vertices[Q[i].vertex], vertices[Q[parent(i)].vertex]);
        swap(Q[i], Q[parent(i)]);
        i = parent(i);
    }
}

void change(element *Q, int *vertices, int vertex, int weight){
    if(vertices[vertex] == 0)
        insert(Q, vertices, vertex, weight);
    else{
        Q[vertices[vertex]].distance = weight;
        int i = vertices[vertex];

        while(i>1 && Q[i].distance < Q[parent(i)].distance) { // after decreasing distance reestablishing structure of the heap
            swap(vertices[Q[i].vertex], vertices[Q[parent(i)].vertex]);
            swap(Q[i], Q[parent(i)]);
            i = parent(i);
        }
    }
}

element get(element Q[N], int *vertices){
    element res = Q[1];

    Q[1] = Q[size];
    swap(vertices[Q[1].vertex], vertices[Q[size].vertex]);

    size--;
    heapify(Q, vertices, 1);
    return res;
}

bool empty(element *Q) {
    return size == 0;
}

int Prim(edge **graph){
    int minimum = 0; // minimum spanning tree

    element Q[N+1];     // priority queue
    size = 0;
    int vertices[N+1];  // pointers to i vertex in heap Q
    bool joint[N+1];    // if vertex is joint

    for(int i=1; i<N+1; i++){
        vertices[i]=0;
        joint[i] = false;
    }

    change(Q, vertices, 1, 0);    // adding vertex 1 (that we are starting with) with weight 0

    while(!empty(Q)){
        element curr = get(Q, vertices);
        joint[curr.vertex] = true;

        edge *tmp = graph[curr.vertex];

        while(tmp->next != nullptr){
            if(!joint[tmp->next->vertex] &&
            (vertices[tmp->next->vertex] == 0 || Q[vertices[tmp->next->vertex]].distance > tmp->next->weight))
                change(Q, vertices, tmp->next->vertex, tmp->next->weight);

            tmp = tmp->next;
        }
        minimum += curr.distance;

    }
    return minimum;
}

void c10_Prim(){
    edge *graph[N+1];

    for(int i=0; i<N+1; i++){
        graph[i] = new edge;
        graph[i]->next = nullptr;
    }

    add_edge(graph, 1, 2, 5);
    add_edge(graph, 1, 3, 2);
    add_edge(graph, 1, 4, 2);
    add_edge(graph, 2, 3, 1);
    add_edge(graph, 3, 4, 3);
    add_edge(graph, 4, 2, 1);

    cout<< Prim(graph)<<endl;

    print(graph);
}