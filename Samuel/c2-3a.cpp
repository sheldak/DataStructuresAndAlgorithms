#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 3;
const int MAX = 10;

struct cont{
    int u;
    int d;
};

int partition(cont t[], int p, int r){
    int x = t[r].u;
    int i = p-1;

    for(int j=p; j<r; j++){
        if(t[j].u < x){
            i++;
            swap(t[i], t[j]);
        }
    }
    swap(t[r], t[i+1]);
    return i+1;
}

void quickSort(cont t[N], int p, int r){
    if(p<r){
        int q = partition(t, p, r);
        quickSort(t, p, q-1);
        quickSort(t, q+1, r);

    }
}

// f(A) = h;  g(h) = A; wszystkie pojemniki tej samej szerokosci; pole przekroju rowne 1 dm^2

int g(cont t[N], int h){
    int sum = 0;

    for(int i=0; i<N; i++){
        if(h >= t[i].u)
            sum += (t[i].u -t[i].d);
        else if(h < t[i].u && h > t[i].d)
            sum += (h - t[i].d);

    }

    return sum;
}

int f(cont t[N], int A){
    int minn = t[0].d;
    int maxx = t[0].u;

    for(int i=0; i<N; i++){
        if(t[i].d < minn)
            minn = t[i].d;

        if(t[i].u > maxx)
            maxx = t[i].u;
    }

    int MAXXX = maxx;
    int curr_h = (maxx+minn)/2;
    int curr_A = g(t, curr_h);

    int p = 100;
    while(curr_A != A && p>0){
        if(curr_A > A)
            maxx = curr_h;
        else if(curr_A < A)
            minn = curr_h;

        if((maxx+minn)/2 == curr_h){
            if((g(t, curr_h) < A && g(t, curr_h+1) > A)|| maxx == MAXXX)
                return curr_h;
        }
        else
            curr_h = (maxx+minn)/2;

        curr_A = g(t, curr_h);

        p--;
    }

    return curr_h;
}

int full(cont t[N], int A){
    int h = f(t, A);

    int sum = 0;

    int i=0;
    while(t[i].u <= h && i<N){
        sum++;
        i++;
    }

    return sum;
}

void c2_3a(){
    srand(time(nullptr));

    cont tab[N];

    for(int i=0; i<N; i++) {
        int x =rand()%(MAX-1);
        tab[i].d = x;
        tab[i].u = x + rand()%(MAX - x) + 1;
        cout<<tab[i].d<<" "<<tab[i].u<<endl;
    }
    cout<<endl;

    int A = rand()%MAX;
    cout<<A<<endl;
    cout<<endl;

    quickSort(tab, 0, N-1);

    for(int i=0; i<N; i++)
        cout<<tab[i].d<<" "<<tab[i].u<<endl;

    cout<<endl;


    cout<<full(tab, A);
}