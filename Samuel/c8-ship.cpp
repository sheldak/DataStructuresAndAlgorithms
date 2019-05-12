// Kapitan statku jest na pozycji x,y. Moze sie poruszyc na sasiednie pole tylko gdy jego glebokosc przekroczy T.
// Sprawdzic czy jest w stanie wplynac do portu.

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 4;
const int T = 5;

struct node{
    node *parent;
    int rank;
};

node *make_tree(){
    node *tree =  new node;
    tree->parent = tree;
    tree->rank = 0;
    return tree;
}

node *find(node *tree){
    if(tree->parent == tree)
        return tree;

    tree->parent = find(tree->parent);

    return tree->parent;
}

void unionn(node *x, node *y){
    node *rx = find(x);
    node *ry = find(y);

    if(rx == ry) return;

    if(rx->rank < ry->rank)
        rx->parent = ry;
    else{
        ry->parent = rx;

        if(rx->rank == ry->rank)
            rx->rank++;
    }
}

bool trip(int depth[N][N], int ship_x, int ship_y){
    node *tree[N][N];

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++)
            tree[y][x] = make_tree();
    }

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            if(depth[y][x] >= T){
                if(y+1 < N && depth[y+1][x] >= T)
                    unionn(tree[y][x], tree[y+1][x]);
                if(x+1 < N && depth[y][x+1] >= T)
                    unionn(tree[y][x], tree[y][x+1]);
            }
        }
    }

    bool res = (find(tree[0][0]) == find(tree[ship_y][ship_x]));

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++)
            delete tree[y][x];
    }

    return res;
}

void c8_ship(){
    srand(time(nullptr));

    int depth[N][N];

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++)
            depth[y][x] = rand()%10;
    }

    int ship_x = rand()%N;
    int ship_y = rand()%N;
    depth[0][0] = T;
    depth[ship_y][ship_x] = T;

    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++)
            cout<<depth[x][y]<<" ";

        cout<<endl;
    }
    cout<<ship_y<<" "<<ship_x<<endl<<endl;

    cout<<((trip(depth, ship_x, ship_y)) ? "T" : "N" );
}