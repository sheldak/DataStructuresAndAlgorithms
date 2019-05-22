//   Ścieżka Hamiltona przechodzi przez wszystkie wierzchołki w grafie,
//   przez każdy dokładnie jeden raz. Proszę zaimplementować algorytm, który
//   stwierdzi czy istnieje ścieżka Hamiltona w acyklicznym grafie skierowanym.


#include <iostream>
using namespace std;

const int N = 5; // number of vertices

struct edge{
    int vertex;
    edge *next;
};

void add_edge(edge **graph, int from, int to){      // for directed graphs
    edge *n = new edge;
    n->vertex = to;
    n->next = nullptr;

    edge *curr = graph[from];
    while(curr->next != nullptr)
        curr = curr->next;

    curr->next = n;
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

void dfs(edge **graph, int curr, bool *visited, int *sorted, int *vertex){

    edge *tmp = graph[curr];
    while(tmp->next != nullptr){
        if(!visited[tmp->next->vertex])
            dfs(graph, tmp->next->vertex, visited, sorted, vertex);

        tmp = tmp->next;
    }

    sorted[*vertex] = curr;
    visited[curr] = true;
    *vertex -= 1;
}

void sortTop(edge **graph, int *sorted){
    bool visited[N+1];
    int vertices = N;
    int *vertex = &vertices;

    for(int i=0; i<N+1; i++){
        visited[i] = false;
        sorted[i] = 0;
    }

    int curr = 1;
    while(vertices > 0){
        if(!visited[curr])
            dfs(graph, curr, visited, sorted, vertex);
        curr++;
    }
}

bool Hamilton(edge **graph){
    int sorted[N+1];
    sortTop(graph, sorted);

    for(int i=2; i<N+1; i++){
        edge *curr = graph[sorted[i-1]];
        while(curr->next != nullptr && curr->next->vertex != sorted[i])
            curr = curr->next;
        if(curr->next == nullptr)
            return false;
    }
    return true;
}

/* O(N^2) :c
bool search(edge **graph, int curr, int rem, bool *visited){
    if(!visited[curr] && rem == 1)
        return true;

    if(visited[curr])
        return false;

    cout<<curr<<endl;
    visited[curr] = true;

    edge *adj = graph[curr];
    cout<<curr<<endl;
    while(adj->next != nullptr){
        cout<<curr<<endl;
        if(search(graph, adj->next->vertex, rem-1, visited))
            return true;
        adj = adj->next;
    }

    visited[curr] = false;
    return false;

}

bool Hamilton(edge **graph){
    bool visited[N+1];
    for(int i=0; i<N; i++)
        visited[i] = false;

    for(int i=1; i<N+1; i++){
        if(search(graph, i, N, visited))
            return true;
    }
    return false;
}
 */

void c10_hamilton(){
    edge *graph[N+1];

    for(int i=0; i<N+1; i++){
        graph[i] = new edge;
        graph[i]->next = nullptr;
    }

    add_edge(graph, 1, 2);
    add_edge(graph, 1, 4);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 5);
    add_edge(graph, 4, 2);
    add_edge(graph, 4, 3);
    add_edge(graph, 4, 5);

    cout<< (Hamilton(graph) ? "Y" : "N")<<endl;

    print(graph);
}