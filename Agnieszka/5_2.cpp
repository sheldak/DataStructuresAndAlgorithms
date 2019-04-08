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
        root = new node;
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
int reverseNth(node *root){
    return (root->rt ==nullptr) ? 1 : (root->rt->chil+1);

}
main(){
    node *root = NULL;
    root = insert(root, 5);
    cout<<root->key<<endl;
    insert(root, 3);
    insert(root, 2);
    insert(root, 4);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);
    cout<<reverseNth(root);
}
