#include <limits.h>
#include <iostream>
#include<math.h>
#include<list>
#define V 5
using namespace std;

int minKey(int key[], bool mstSet[]) // finds vertex not in mstSet w minimum key
{
int mini = INT_MAX, min_index;

for (int v = 0; v < V; v++)
	if (mstSet[v] == false && key[v] < mini)
		mini = key[v], min_index = v;

return min_index;
}

void primMST(double graph[V][V], list<int> children[V])
{
	int *parent = new int[V];
	int *key = new int[V];
	bool *mstSet = new bool[V];

	for (int i = 0; i < V; i++)
		key[i] = INT_MAX, mstSet[i] = false;

	key[0] = 0;
	parent[0] = -1;

	for (int cnt = 0; cnt < V-1; cnt++)
	{
		int u = minKey(key, mstSet);

		mstSet[u] = true;

		for (int v = 0; v < V; v++){
            if (graph[u][v]>0 && mstSet[v] == false && graph[u][v] < key[v]){
                parent[v] = u;
                key[v] = graph[u][v];
            }
		}
	}
    for(int i=1;i<V;i++){
        children[parent[i]].push_back(i);
    }
}

double dst(int x, int y, int a, int b){
    return sqrt(double((x-a)*(x-a)+(y-b)*(y-b)));
}
void preorder(double graph[V][V], list<int> *children, int &prev, int v, double &res){
    res+=graph[prev][v];
    cout<<"edge "<<prev<<" "<<v<<" sum "<<res<<endl;
    prev = v;
    list<int>::iterator it = children[v].begin();
    for( ;it!=children[v].end();++it){
        preorder(graph, children, prev, *it, res);
    }
}
double TSP(double graph[V][V]){
    list<int> children[V];
    primMST(graph, children);
    double ans = 0;
    int prev=0;
    list<int>::iterator it = children[0].begin();
        for( ;it!=children[0].end();++it){
                preorder(graph, children, prev, *it, ans);
        }
    ans+=graph[prev][0];
    cout<<"edge "<<prev<<" "<<0<<" sum "<<ans<<endl;
    return ans;
}
int main()
{
    int points[V][2] = {{0,0},{1,0},{0,1},{-1,0},{0,-1}};
    double graph[V][V];
    for(int i=0;i<V;i++){
        for(int j=i;j<V;j++){
            graph[i][j] = graph[j][i] = dst(points[i][0], points[i][1], points[j][0], points[j][1]);
            //cout<<i<<" "<<j<<" "<<graph[i][j]<<endl;
        }
    }
	cout<<TSP(graph);

	return 0;
}
