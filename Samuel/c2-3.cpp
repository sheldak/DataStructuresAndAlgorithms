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
    int minn = c[0].dr.y;
    int maxx = c[0].ul.y;

    for(int i=1; i<N; i++){
        if(c[i].dr.y < minn)
            minn = c[i].dr.y;
        if(c[i].ul.y > maxx)
            maxx = c[i].ul.y;
    }

    int *t = nullptr;
    t = new int[maxx-minn+1];

    for(int i=0; i<MAX; i++)
        t[i] = 0;

    for(int i=0; i<N; i++){
        int k=c[i].dr.y - minn;
        while(k<=c[i].ul.y - minn){
            t[k] = t[k] + c[i].dr.x - c[i].ul.x;
            k++;
        }
    }

    curr_h = minn;
    while(A>0 && curr_h <= maxx)
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
