#include <bits/stdc++.h>
using namespace std;

void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

bool isBipartite(vector<int> adj[], int v, int N)
{
    int *color = new int[N+1];
    for(int i=0;i<=N;i++) color[i]=-1;
    color[v] = 1;
    queue <int> q;
    q.push(v);
    while(!q.empty()){
        int u= q.front();
        q.pop();
        for (int a : adj[u]) {
            if (color[a] == -1) {
                color[a] = 1-color[u];
                q.push(a);
            }
            else if (color[a] == color[u])
                return false;
        }
    }
	return true;
}

int main()
{
	int N = 6;

	vector<int> adj[N + 1];
	addEdge(adj, 1, 2);
	addEdge(adj, 2, 3);
	addEdge(adj, 3, 4);
	addEdge(adj, 4, 5);
	addEdge(adj, 5, 6);
	addEdge(adj, 6, 1);
	if (isBipartite(adj, 1, N)) {
		cout << "Graph is Bipartite";
	}
	else {
		cout << "Graph is not Bipartite";
	}

	return 0;
}
