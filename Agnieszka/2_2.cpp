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
    node *p= new node;
    p->val=n;
    p->next=head;
    head=p;
}
void insertt(node *el, node *sorted){
    while(sorted->next!=nullptr && sorted->next->val<el->val){
        sorted=sorted->next;
    }
    el->next=sorted->next;
    sorted->next=el;
}
node* insort(node *head){
    node *sorted= new node;
    sorted->next=nullptr;
    while(head!=nullptr){
        node *tmp=head;
        head=head->next;
        tmp->next=nullptr;
        insertt(tmp, sorted);
    }
    node *del=sorted;
    sorted=sorted->next;
    delete del;
    return sorted;
}
void nsort(int *tab, int n){
    node *aux[n]; /// [0-(n-1)][n-(2n-1)]...[n*(n-1)-(n*n-1)]
    int ind=0;
    for(int i=0;i<n;i++) aux[i]=nullptr;
    for(int i=0;i<n;i++){
        add(aux[tab[i]/n], tab[i]);
    }
    for(int i=0;i<n;i++){
        aux[i]=insort(aux[i]);
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
