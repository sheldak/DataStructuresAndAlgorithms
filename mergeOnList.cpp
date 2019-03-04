#include<iostream>
using namespace std;
struct node{
    int val;
    node *next;
};
void display(node *l){
    while(l!=nullptr){
        cout<<l->val<<" ";
        l=l->next;
    }
    cout<<endl;
}
int getSize(node *head){
    int ret=0;
    while(head!=nullptr){
        ret++;
        head=head->next;
    }
    return ret;
}
node *mergeS(node *l, node*r){
    node *ret=new node;
    ret->next=nullptr;
    node *it=ret;
    while(l!=nullptr &&r!=nullptr){
        node *p=new node;
        if(l->val<r->val){
            p->val=l->val;
            l=l->next;
        }
        else{
            p->val=r->val;
            r=r->next;
        }
        p->next=nullptr;
        it->next=p;
        it=it->next;
    }
    if(l!=nullptr){
        it->next=l;
    }
    if(r!=nullptr){
        it->next=r;
    }
    node *p=ret;
    ret=ret->next;
    delete p;
    return ret;

}
void mergeSort(node *&head, int n=0){
    display(head);
    if(head==nullptr || n==1) return;
    if(n==0) n=getSize(head);
    node *mid;
    node *l;
    node *tmp=head;
    for(int i=1;i<n/2;i++)//1 obrot mniej
        tmp=tmp->next;
    mid=tmp->next;
    tmp->next=nullptr;
    l=head;
    mergeSort(l,n/2);
    mergeSort(mid,(n+1)/2);
    head=mergeS(l,mid);
    return;
}

void add(node *&head, int v){
    node *p=new node;
     p->next=head;
     p->val=v;
     head=p;
}
main(){
    node *head=new node;
    head->val=5;
    head->next=nullptr;
    add(head,3);
    add(head,4);
    add(head,7);
    mergeSort(head);
    display(head);
}
