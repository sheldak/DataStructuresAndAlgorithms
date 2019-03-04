#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 31;

int missing(int t[N]){
    int l=0, r=N-1;

    while(r-l != 1){
        cout<<l<<" "<<r<<endl;
        if((l+r)/2 + t[0] == t[(l+r)/2])
            l = (l+r)/2;
        else
            r = (l+r)/2;
    }
    return l+t[0]+1;
}

void c0_d4(){
    srand(time(nullptr));
    int t[N];

    int x = rand()%100;
    int y = x + rand()%(N-2) + 1;
    for(int i=x; i<N+x; i++) {
        if(i<y)
            t[i-x] = i;
        else
            t[i-x] = i+1;

        cout<<t[i-x]<<" ";
    }
    cout<<endl;

    cout<<missing(t);
}