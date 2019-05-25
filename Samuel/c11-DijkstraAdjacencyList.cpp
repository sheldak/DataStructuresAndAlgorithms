#include <iostream>
#define size Q[0].distance

using namespace std;

const int N = 8;

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

void insert(element *Q, int *distance, int *vertices, int vertex, int weight){
    size++;
    Q[size].vertex = vertex;
    Q[size].distance = weight;
    distance[vertex] = weight;
    vertices[vertex] = size;
    int i=size;

    while(i>1 && Q[i].distance < Q[parent(i)].distance) {   // after adding new element reestablishing structure of the heap
        swap(vertices[Q[i].vertex], vertices[Q[parent(i)].vertex]);
        swap(Q[i], Q[parent(i)]);
        i = parent(i);
    }
}

void change(element *Q, int *distance, int *vertices, int vertex, int weight){
    if(vertices[vertex] == 0)
        insert(Q, distance, vertices, vertex, weight);
    else{
        Q[vertices[vertex]].distance = weight;
        distance[vertex] = weight;
        int i = vertices[vertex];

        while(i>1 && Q[i].distance < Q[parent(i)].distance) { // after decreasing distance reestablishing structure of the heap
            swap(vertices[Q[i].vertex], vertices[Q[parent(i)].vertex]);
            swap(Q[i], Q[parent(i)]);
            i = parent(i);
        }
    }
}

element get(element *Q, int *vertices){
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

/*void print_path(int s, int t, int parent[N]){
    if(s == t){
        cout<<"Path: "<<s<<" ";
    }
    else{
        print_path(s, parent[t], parent);
        cout<<t<<" ";
    }
}

int minn(int distance[N], bool visited[N]){
    int minn = INT32_MAX;
    int vertex = 0;
    for(int i=0; i<N; i++){
        if(minn > distance[i] && !visited[i]) {
            minn = distance[i];
            vertex = i;
        }
    }
    return vertex;
}*/

void relax(element Q[N], int vertices[N], int distance[N], element u, edge *w){
    if(distance[w->vertex] > distance[u.vertex] + w->weight){
        change(Q, distance, vertices, w->vertex, u.distance+w->weight);
    }
}

int Dijkstra(edge **Graph, int s, int t){

    element Q[N+1];
    size = 0;
    int distance[N];
    int vertices[N];

    for(int i=0; i<N; i++)
        insert(Q, distance, vertices, i, INT32_MAX);


    change(Q, distance, vertices, s, 0);

    for(int i=0; i<N; i++){
        element curr = get(Q, vertices);

        edge *tmp = Graph[curr.vertex];
        while(tmp -> next != nullptr){
            relax(Q, vertices, distance, curr, tmp->next);
            tmp = tmp->next;
        }
    }

    return distance[t];
}

void c11_Dijkstra(){
    edge *Graph[N];

    for(int i=0; i<N; i++){
        Graph[i] = new edge;
        Graph[i]->next = nullptr;
    }

    add_edge(Graph, 0, 1, 1);
    add_edge(Graph, 0, 2, 4);
    add_edge(Graph, 0, 3, 5);
    add_edge(Graph, 1, 4, 3);
    add_edge(Graph, 2, 3, 2);
    add_edge(Graph, 2, 5, 2);
    add_edge(Graph, 3, 4, 5);
    add_edge(Graph, 3, 5, 1);
    add_edge(Graph, 3, 6, 7);
    add_edge(Graph, 3, 7, 2);
    add_edge(Graph, 4, 6, 8);
    add_edge(Graph, 4, 7, 2);
    add_edge(Graph, 5, 6, 9);
    add_edge(Graph, 6, 7, 4);

    cout<<Dijkstra(Graph, 0, 6);


}