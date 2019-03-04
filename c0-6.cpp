#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 30;

void c0_6(){
    srand(time(nullptr));
    int t[N];

    for (int i=0; i<N; i++){    // randomization
        t[i] = rand() % 100;
        cout << t[i] << " ";
    }
    cout<<endl;

    int minn=t[0], maxx=t[0];
    int i;
    for(i=1 ; i<N-1; i+=2){
        if(t[i] > t[i+1]){
            if(t[i] > maxx)
                maxx = t[i];
            if(t[i+1] < minn)
                minn = t[i+1];
        }
        else{
            if(t[i+1] > maxx)
                maxx = t[i+1];
            if(t[i] < minn)
                minn = t[i];
        }
    }
    if(i == N-1){
        if(t[i] > maxx)
            maxx = t[i];
        if(t[i] < minn)
            minn = t[i];
    }

    cout<<"max: "<<maxx<<endl;
    cout<<"min: "<<minn;
}