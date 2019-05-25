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

void heapify(element Q[N], int i){
    int l = left(i);
    int r = right(i);

    int minn = i;

    if(l<size && Q[l].distance < Q[minn].distance)
        minn = l;
    if(r<size && Q[r].distance < Q[minn].distance)
        minn = r;
    if(minn != i) {
        swap(Q[minn], Q[i]);
        heapify(Q, minn);
    }
}

void insert(element *Q, int vertex, int weight){
    size++;
    Q[size].vertex = vertex;
    Q[size].distance = weight;
    int i=size;

    while(i>1 && Q[i].distance < Q[parent(i)].distance) {   // after adding new element reestablishing structure of the heap
        swap(Q[i], Q[parent(i)]);
        i = parent(i);
    }
}

element get(element Q[N]){
    element res = Q[1];

    Q[1] = Q[size];

    size--;
    heapify(Q, 1);
    return res;
}

bool empty(element *Q) {
    return size == 0;
}

// GRAPH
void add_edge(int Graph[N][N], int from, int to, int weight){
    Graph[from][to] = weight;
    Graph[to][from] = weight;
}

void print_path(int s, int t, int parent[N]){
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
}

void relax(int Graph[N][N], int *distance, int *parent, int u, int w){
    if(distance[w] > distance[u] + Graph[u][w]){
        distance[w] = distance[u] + Graph[u][w];
        parent[w] = u;
    }
}

int Dijkstra(int Graph[N][N], int s, int t){
    int distance[N];
    int parent[N];
    bool visited[N];

    for(int i=0; i<N; i++){
        distance[i] = INT32_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    distance[s] = 0;

    while(!visited[t]){
        int curr = minn(distance, visited);
        visited[curr] = true;

        for(int i=0; i<N; i++){
            if(Graph[curr][i] != -1){
                relax(Graph, distance, parent, curr, i);
            }
        }
    }

    print_path(s, t, parent);
    cout<<endl<<"Distance: ";

    return distance[t];

}

void c11_Dijkstra(){
    int Graph[N][N];

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            Graph[i][j] = -1;
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