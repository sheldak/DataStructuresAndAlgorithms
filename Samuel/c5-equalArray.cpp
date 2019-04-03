/* Given a an array of n elements such that elements may repeat. We can delete any number of elements from array. The
 * task is to find minimum number of elements to be deleted from array to make it equal (every element in array equal)*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 20;

struct element{
    int value;
    int number;
    bool full;
};

void print(element T[]){        // just for checking if it works
    for(int i=0; i<2*N; i++){
        if(i==0)
            cout<<"{";

        if(!T[i].full)
            cout<<"#";
        else
            cout<<T[i].value<<": "<<T[i].number;

        if(i<=2*N-2)
            cout<<", ";
        else
            cout<<"}";
    }
    cout<<endl;
}

int hashh(int value, int it){
    int res = 0;
    res =(value * 19 + it*it*13)%(2*N);
    return res;
}

void insert(element T[], int v, int &maxx){
    int it=0;

    while(T[hashh(v, it)].full && T[hashh(v, it)].value != v)
        it++;

    if(!T[hashh(v, it)].full){
        T[hashh(v, it)].full = true;
        T[hashh(v, it)].value = v;
        T[hashh(v, it)].number = 1;
    }
    else
        T[hashh(v, it)].number++;

    if(T[hashh(v, it)].number > maxx)
        maxx = T[hashh(v, it)].number;

}

int minimum(int T[]){
    element hashMap[2*N];

    int maxx = 0;

    for(int i=0; i<2*N; i++)
        hashMap[i].full = false;

    for(int i=0; i<N; i++)
        insert(hashMap, T[i], maxx);

    print(hashMap);

    return N-maxx;

}

void c5_equalArray(){
    srand(time(nullptr));

    int T[N];
    for(int i=0; i<N; i++){
        T[i] = rand()%(N/2);
        cout<<T[i]<<" ";
    }
    cout<<endl;

    cout<<minimum(T);
}