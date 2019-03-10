#include<iostream>
using namespace std;
const int N=1000;

main(){
    int n,A;
    int X[N+1]; // N - najwieksza wspolrzedna
    for(int i=0;i<=N;i++) X[i]=0;
    printf("ile pojemnikow: ");
    scanf("%d",&n);
    int *cont= new int[n]; // zapisuje gorna krawedz pojemnika
    printf("ile litrow wody: ");
    scanf("%d",&A);
    int yH, yL, xL, xR;
    for(int i=0;i<n;i++){
        cin>>xL>>yH>>xR>>yL;
        int width=xR-xL;
        for(int i=yL+1;i<=yH;i++){
            X[i]+=width;
        }
        cont[i]=yH;
    }
    int sum=0, height=0;
    while(sum<A){
        height++;
        sum+=X[height];
    }
    if(sum>A) height--; // zbiorniki na kolejnym pietrze nie zostalyby zapelnione w calosci
    int ans=0;
    for(int i=0;i<n;i++){
        if(cont[i]<=height) ans++;
    }
    cout<<ans;

}
