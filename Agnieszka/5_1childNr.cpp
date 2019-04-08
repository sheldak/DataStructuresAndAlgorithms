#include<iostream>
using namespace std;
struct node{
    int key;
    node *lt;
    node *rt;
    node *par;
    int chil;
};
node *insert(node* root, int key, node *prev=nullptr){
    if(root==nullptr) {
        root->key=key;
        root->par=prev;
        root->lt=nullptr;
        root->rt=nullptr;
        root->chil=1;
        return root;
    }
    root->chil++;
    if (key < root->key)
        root->lt  = insert(root->lt, key, root);
    else if (key > root->key)
        root->rt = insert(root->rt, key, root);
    return root;
}
node* findMin(node* nod){
    if(nod==nullptr) return nod;
    if(nod->lt==nullptr) return nod;
    return findMin(nod->lt);
}
node* findMax(node* nod){
    if(nod==nullptr) return nod;
    if(nod->rt==nullptr) return nod;
    return findMax(nod->rt);
}
struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL) return root;
    if (key < root->key)
        root->lt = deleteNode(root->lt, key);
    else if (key > root->key)
        root->rt = deleteNode(root->rt, key);
    else{ // root is the node that we want to delete
        if (root->lt == NULL){
                //decrement parents
            struct node *temp = root->rt;
            delete root;
            return temp;
        }
        else if (root->rt == NULL){
            //decr
            struct node *temp = root->lt;
            delete root;
            return temp;
        }
        struct node* temp = findMin(root->rt);
        root->key = temp->key;
        root->rt = deleteNode(root->rt, temp->key);
    }
    return root;
}
node* findNth(node *root, int n){
    if(n> root->chil) return nullptr;
    if(root->rt==nullptr){
        if(n==1) return root;
        return findNth(root->lt, n-1);
    }
    if(root->rt->chil >=n)
        return findNth(root->rt, n);
    if(root->rt->chil ==n-1) return root;
    return findNth(root->lt, n-(root->rt->chil+1));
}
main(){
}
