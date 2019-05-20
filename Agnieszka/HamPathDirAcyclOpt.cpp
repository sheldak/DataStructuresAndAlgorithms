#include <iostream>
#include <stack>

using namespace std;
struct Node{
    int v;
    Node *next;
};
struct Graph{
    int N;
    Node **adj;
    Graph(int n){
        N = n;
        adj = new Node*[n+1];
        for(int i=0;i<=n;i++)
            adj[i] = nullptr;
    }
    void addEdge(int u, int v){
        Node *tmp = new Node;
        tmp->v=v;
        tmp->next = adj[u];
        adj[u] = tmp;
    }
    void allAdj(int u){
        Node *it = adj[u];
        while(it!=nullptr){
            cout<<it->v;
            it=it->next;
        }
    }
};
int topSortUtil(Graph g, int ind, int *in, int v){
    ind++;
    stack<int> s;
    Node *it = g.adj[v];
        while(it!=nullptr){
            in[it->v]--;
            if(in[it->v]==0){
                s.push(it->v);
            }
            it=it->next;
        }
        if(s.empty()) return ind;
        ind = topSortUtil(g, ind, in, s.top());
            s.pop();
        if(!s.empty()) return ind; // no way of reaching those
    return ind;
}
bool topSort(Graph g){
    int in[g.N+1];
    int ind=0;
    for(int i=0;i<=g.N;i++) in[i]=0;
    for(int i=1;i<=g.N;i++){ // num starts from 1
        Node *it = g.adj[i];
        while(it!=nullptr){
            in[it->v]++;
            it=it->next;
        }
    }
    for(int i=1;i<=g.N;i++){
        if(in[i]==0){
            ind = topSortUtil(g, ind, in, i);
            break; // only for ham path
        }
    }
    if(ind<g.N) return false;
    return true;
}

bool hamPath(Graph g){
    return topSort(g);
}

int main(){
    Graph g(5);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(4,5);
    g.addEdge(5,3);
    cout<<hamPath(g);

}
