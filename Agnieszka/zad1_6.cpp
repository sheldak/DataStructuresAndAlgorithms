// structure containing natural numbers where insert() removeMin() and removeMax() has O(log n) complexity
#include<iostream>
using namespace std;
const int N=100;
struct heap{
    int hsize;
    heap() : hsize(0) {}
    int h[N];
    int vMin[N];
    int vMax[N];
};
inline int parent(int i){return i/2;}

void hinsert(heap hip, int i){
    hip.hsize++;
    int ind=hip.hsize;
    hip.h[ind]=i;
    hip.vMax[ind]=hip.vMin[ind]=i;
        bool change=true;
    while(ind>1 && change){
        change = false;
        if(hip.vMax[ind]>hip.vMax[parent(ind)]){
            change=true;
            hip.vMax[parent(ind)]=i;
        }
        if(hip.vMin[ind]<hip.vMin[parent(ind)]){
            change=true;
            hip.vMin[parent(ind)]=i;
        }
        ind=ind/2;
    }
}

int getMin(heap hip,int ind){
    int ret = hip.h[ind];
    if(ind*2>hip.hsize) // no children
        return ret;
    if(ind*2+1>hip.hsize) // only left child
        return min(ret, hip.vMin[ind*2]);
    else{
        ret=min(ret, hip.vMin[ind*2]);
        ret=min(ret, hip.vMin[ind*2+1]);
        return ret;
    }
}
int getMax(heap hip,int ind){
    int ret = hip.h[ind];
    if(ind*2>hip.hsize) // no children
        return ret;
    if(ind*2+1>hip.hsize) // only left child
        return max(ret, hip.vMax[ind*2]);
    else{
        ret=max(ret, hip.vMax[ind*2]);
        ret=max(ret, hip.vMax[ind*2+1]);
        return ret;
    }
}

void fix(heap hip, int ind){
    bool change = true;
    ind=ind/2;
    while(ind>=1 && change){ // as long as parents've been affected keep recalculating their Min Max
            change = false;
            int vMax=getMax(hip, ind);
            int vMin=getMin(hip, ind);
        if( hip.vMax[ind] != vMax ){
            change = true;
            hip.vMax[ind]= vMax;
        }
        if( hip.vMin[ind] != vMin ){
            change = true;
            hip.vMin[ind]= vMin;
        }
        ind=ind/2;
    }
}

void removeMin(heap hip){
    int ind =1; // finding index of minimum el
    while(hip.vMin[ind]!=hip.h[ind]){ // at least left child exists
        int l=ind*2, r=ind*2+1;
        if(hip.vMin[l]==hip.vMin[ind]){
            ind=l;
        }
        else{
            ind=r;
        }
    }
    int ret=hip.h[ind]; // searched value
    int last=hip.h[hip.hsize];
    hip.h[ind]=last; // putting last element in the place of the smallest one
    hip.hsize--;
    fix(hip, hip.hsize+1); // fix parents of moved last element
    hip.vMin[ind]=getMin(hip, ind);
    hip.vMax[ind]=getMax(hip, ind);
    fix(hip, ind); // fix parents of deleted smallest element

    // return ret; if we want a value
}

main(){

}
