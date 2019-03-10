#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 3;
const int MAX = 7;

struct point{
    int x;
    int y;
};

struct cont{
    point ul;
    point dr;
};

int full(cont c[N], int A){
    int curr_h = 0;
    int t[MAX];
    for(int i=0; i<MAX; i++)
        t[i] = 0;

    for(int i=0; i<N; i++){
        int k=c[i].dr.y;
        while(k<=c[i].ul.y){
            t[k] = t[k] + c[i].dr.x - c[i].ul.x;
            k++;
        }
    }

    while(A>0)
        A-=t[curr_h++];

    int res=0;

    for(int i=0; i<N; i++){
        if(c[i].ul.y <= curr_h-1)
            res++;
    }

    return res;
}

void c2_3(){
    srand(time(nullptr));

    cont c[N];

    for(int i=0; i<N; i++){
        c[i].ul.x = rand()%(MAX-1);
        c[i].dr.y = rand()%(MAX-1);

        c[i].dr.x = c[i].ul.x + rand()%(MAX-1-c[i].ul.x)+1;
        c[i].ul.y = c[i].dr.y + rand()%(MAX-1-c[i].dr.y)+1;
        cout<<c[i].ul.x<<" "<<c[i].dr.x<<" "<<c[i].ul.y<<" "<<c[i].dr.y<<endl;
    }

    int A = rand()%(MAX*N);
    cout<<A<<endl;

    cout<<full(c, A);
}