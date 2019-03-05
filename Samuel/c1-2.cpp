#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 10;

void selectionSort(int t[N][N], int k, int n){
    for(int i=0; i<n-1; i++){
        int minn=i;
        for(int j=i+1; j<n; j++){
            if(t[k][j]<t[k][minn])
                minn = j;
        }
        swap(t[k][i], t[k][minn]);
    }
}

void merge(int t[N], int p[N], int start, int end){
    if(end-start == 0)
        return;

    int s1=0, s2=0;

    if(end-start == 1){
        for(int i=0; i<start; i++)
            s1 += p[i];

        s2 = s1+p[start];

        int i=0, j=0;
        int res[N];
        int k=0;
        while(i<p[start] || j<p[end]){
            if(i>=p[start] || (j<p[end] && t[s1+i]>t[s2+j])){
                res[k++] = t[s2+j];
                j++;
            }
            else{
                res[k++] = t[s1+i];
                i++;
            }
        }

        for(int l=s1; l<s2+p[end]; l++){
            t[l] = res[l-s1];
        }
    }
    else{
        merge(t, p, start, (start+end)/2);
        merge(t, p, (start+end)/2 + 1, end);

        for(int i=0; i<start; i++)
            s1 += p[i];

        s2=s1;
        for(int i=start; i<(start+end)/2 + 1; i++)
            s2 += p[i];

        int f=s2;
        for(int i=(start+end)/2+1; i<=end; i++)
            f+=p[i];

        int i=s1, j=s2;
        int res[N];
        int k=0;
        while(i<s2 || j<f){
            if(i>=s2 || (j<f && t[i]>t[j])){
                res[k++] = t[j];
                j++;
            }
            else{
                res[k++] = t[i];
                i++;
            }
        }

        for(int l=s1; l<f; l++){
            t[l] = res[l-s1];
        }
    }
}

void c1_2(){
    srand(time(nullptr));

    int t[N][N];

    int k = rand()%(N-2)+2;
    cout<<k<<endl;
    for(int i=0; i<k; i++)
        t[i][0] = rand()%100;

    int p[N];
    for(int i=0; i<k; i++)
        p[i] = 1;

    for(int i=0; i<N-k; i++){
        int x = rand()%k;
        t[x][p[x]] = rand()%100;
        p[x]++;
    }

    for(int i=0; i<k; i++)
        t[i][p[i]] = -1;

    for(int i=0; i<k; i++){
        int l=0;
        while(t[i][l] != -1)
            cout<<t[i][l++]<<" ";
        cout<<endl;
    }
    cout<<endl;

    int tab[N];
    int it=0;
    for(int i=0; i<k; i++){
        selectionSort(t, i, p[i]);
        p[i]=0;
        int j=0;
        while(t[i][j] != -1){
            p[i]++;
            tab[it++]=t[i][j++];
        }
    }
    for(int i=0; i<N; i++){
        cout<<tab[i]<<" ";
    }
    cout<<endl;

    merge(tab, p, 0, k-1);

    for(int i=0; i<N; i++)
        cout<<tab[i]<<" ";
}