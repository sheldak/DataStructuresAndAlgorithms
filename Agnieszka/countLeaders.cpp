#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}
void bfs(vector<int> adj[], int v, int N, bool *vis){
    queue <int> q;
    q.push(v);
    vis[v]=1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for (int a : adj[u]) {
            if (vis[a] == 0) {
                vis[a] = 1 ;
                q.push(a);
            }
        }
    }
}
int countLeaders(vector<int> adj[],int N) // vert. 1, 2, ... , N
{
    bool *vis = new bool[N+1];
    for(int i=0;i<=N;i++) vis[i]=0;
    int res=0;
    bfs(adj, 1, N, vis);
    res++;
    for(int i=2;i<=N;i++){
        if(!vis[i]){
            res++;
            bfs(adj, i, N, vis);
        }
    }
	return res;
}
int main()
{
	int N = 8;

	vector<int> adj[N + 1];
	addEdge(adj, 1, 2);
	addEdge(adj, 2, 3);
	addEdge(adj, 3, 4);
	addEdge(adj, 4, 5);
	addEdge(adj, 5, 6);
	addEdge(adj, 6, 1);
	addEdge(adj, 7, 8);
	cout<<countLeaders(adj, N);

	return 0;
}
