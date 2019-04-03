#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const int N=1000;
struct node{
    int val;
    node* next;
};
node *find_node(node*head, int val){
    node *it=head;
    while(it->next != nullptr && it->next->val!=val)
        it=it->next;
    return it;
}
void add_node(node *head, int val){
    node *prev=find_node(head, val);
    if(prev->next!=nullptr) return;
    node *tmp=new node;
    tmp->val=val;
    tmp->next=nullptr;
    prev->next=tmp;
}
void del_node(node *head, int val){
    node *prev=find_node(head, val);
    if(prev->next==nullptr) return;
    node *tmp=prev->next;
    prev->next=prev->next->next;
    delete tmp;
    return;
}
struct hashArray{
    node **ar;
    int siz;
    hashArray(int);
};
hashArray::hashArray(int n){
    siz=n;
    ar=new node*[n];
    for(int i=0;i<n;i++){
        ar[i]=new node;
        ar[i]->next=nullptr;
    }
}
int hashFun(int val, int siz){
    return val%siz;
}
void add_el(hashArray *A, int val){
    add_node( A->ar[hashFun(val, A->siz)], val);
}
void del_el(hashArray *A, int val){
    del_node(A->ar[hashFun(val, A->siz)], val);
}
node* find_el(hashArray *A, int val){
    return find_node(A->ar[hashFun(val, A->siz)], val);
}

main(){


}
