// 1. Proszę zaimplementować następujące algorytmy:
//  - Sprawdzanie czy graf jest dwudzielny
//  - Policzyć liczbę spójnych składowych w grafie
//  Graf jest reprezentowany jako macierz sąsiedztwa albo listy sąsiadów albo listy krawędzi.

// tutaj graf jest reprezentowany jako lista sasiadow

#include <iostream>
#include <queue>
using namespace std;

const int N = 5; // number of vertices

struct edge{
    int vertex;
    edge *next;
};

void add_edge_dir(edge **graph, int from, int to){      // for directed graphs
    edge *n = new edge;
    n->vertex = to;
    n->next = nullptr;

    edge *curr = graph[from];
    while(curr->next != nullptr)
        curr = curr->next;

    curr->next = n;
}

void add_edge(edge **graph, int st, int nd){            // for undirected graphs
    edge *n = new edge;
    n->vertex = nd;
    n->next = nullptr;

    edge *curr = graph[st];
    while(curr->next != nullptr)
        curr = curr->next;

    curr->next = n;

    edge *m = new edge;
    m->vertex = st;
    m->next = nullptr;

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

bool bipartite_graph(edge **graph){
    int vertices[N+1] = {};     // vertices and their belonging to one of parts of bipartite graph

    int first_disjoint = 2;
    queue <int> Q;
    Q.push(1);
    while(!Q.empty() || first_disjoint < N+1){
        if(Q.empty()) {     // checking disjoint parts of graph
            while(first_disjoint < N+1 && vertices[first_disjoint]==0)
                first_disjoint++;

            if(first_disjoint < N+1){
                Q.push(first_disjoint);
                first_disjoint++;
            }
        }

        if(!Q.empty()){             // vertices: 1 - not visited yet and 1st part, 2 - not visited yet and 2nd part
                                    //           3 - visited and 1st part,         4 - visited and 2st part
            int i = Q.front();
            Q.pop();
            if(vertices[i] < 3){
                edge *curr = graph[i];

                if(vertices[i] == 0)
                    vertices[i] = 1;

                while(curr->next != nullptr){
                    if(vertices[curr->next->vertex]!=0 && vertices[curr->next->vertex]%2==vertices[i]%2){
                        return false;
                    }

                    else if(vertices[curr->next->vertex]==0){
                        if(vertices[i] == 1)
                            vertices[curr->next->vertex] = 2;
                        else
                            vertices[curr->next->vertex] = 1;
                        Q.push(curr->next->vertex);
                    }

                    curr = curr->next;
                }

                vertices[i] += 2;
            }
        }
    }

    cout<<"{";
    for(int i=1; i<N+1; i++)            // printing array
        cout<<vertices[i]<<((i<N) ? ", " : "}");
    cout<<endl;

    return true;
}

int components(edge **graph){
    int res = 1;
    int vertices[N+1] = {};     // 0 - not visited, 1 - visited

    queue <int> Q;

    Q.push(1);
    int first_disjoint = 2;

    while(!Q.empty() || first_disjoint < N+1){
        if(Q.empty()){      // checking disjoint
            while(first_disjoint < N+1 && vertices[first_disjoint] == 1)
                first_disjoint++;

            if(first_disjoint < N+1){
                res++;
                Q.push(first_disjoint);
                first_disjoint++;
            }
        }
        if(!Q.empty()){     // bfs
            int i = Q.front();
            Q.pop();

            if(vertices[i] == 0){
                vertices[i] = 1;

                edge *curr = graph[i];
                while(curr->next != nullptr){
                    Q.push(curr->next->vertex);
                    curr = curr->next;
                }
            }
        }
    }

    return res;
}

void bipartite_and_components(){
    edge *graph[N+1];

    for(int i=0; i<N+1; i++){
        graph[i] = new edge;
        graph[i]->next = nullptr;
    }

    add_edge(graph, 1, 4);
    add_edge(graph, 1, 3);
    add_edge(graph, 4, 5);
    add_edge(graph, 2, 5);

    print(graph);

    cout<< (bipartite_graph(graph) ? "Y" : "N") <<endl<<endl;


    edge *graphh[N+1];

    for(int i=0; i<N+1; i++){
        graphh[i] = new edge;
        graphh[i]->next = nullptr;
    }

    add_edge(graphh, 1, 2);
    add_edge(graphh, 4, 5);

    print(graphh);

    cout<<components(graphh);
}