#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

const int N = 10;

void bubbleSort(int t[N]){
    for(int i=N-1; i>=1; i--){
        for(int j=0; j<i; j++){
            if(t[j]>t[j+1])
                swap(t[j], t[j+1]);
        }
    }
}

void c0_d3(){
    srand(time(nullptr));
    int t[N];

    for (int i=0; i<N; i++)    // randomization
        t[i] = rand() % 100;

    int x = rand()%100;
    cout<<x<<endl;

    bubbleSort(t);

    for(int i=0; i<N; i++)
        cout<<t[i]<<" ";

    cout<<endl;

    int eps = abs(t[0] + t[N-1] - x);
    int a=0;
    int b=N-1;

    int best_a=0, best_b=N-1;
    while(abs(a-b) >= 2){
        if(t[a]+t[b] > x){
            b--;
            if(eps > abs(t[a] + t[b] - x)){
                eps = abs(t[a] + t[b] - x);
                best_a = a;
                best_b = b;
            }
        }
        else{
            a++;
            if(eps > abs(t[a] + t[b] - x)){
                eps = abs(t[a] + t[b] - x);
                best_a = a;
                best_b = b;
            }
        }
    }

    cout<<t[best_a]<<" "<<t[best_b];


}
