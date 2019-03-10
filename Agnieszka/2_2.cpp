/**
Bucket Sort
**/

#include<iostream>
using namespace std;
const int N=1000;
struct node{
    int val;
    node *next;
};
void add(node*&head, int n){
    node *p=new node;
    p->val=n;
    p->next=nullptr;
    if(head==nullptr || head->val>=n){
        p->next=head;
        head=p;
        return;
    }
    node *curr=head;
    while(curr->next!=nullptr && curr->next->val<n) curr=curr->next;
    p->next=curr->next;
    curr->next=p;
}
void nsort(int *tab, int n){
    node *aux[n]; /// [0-(n-1)][n-(2n-1)]...[n*(n-1)-(n*n-1)]
    int ind=0;
    for(int i=0;i<n;i++) aux[i]=nullptr;
    for(int i=0;i<n;i++){
        add(aux[tab[i]/n], tab[i]);
    }
    for(int i=0;i<n;i++){
        while(aux[i]!=nullptr){
            tab[ind++]=aux[i]->val;
            aux[i]=aux[i]->next;
        }
    }
}
main(){
    int n;
    cin>>n;
    int *tab = new int[n];
    for(int i=0;i<n;i++){
        cin>>tab[i];
    }
    nsort(tab, n);
    for(int i=0;i<n;i++) cout<<tab[i]<<" ";
}
