#include<iostream>
using namespace std;
enum Color{red, black};
struct node{
    int key;
    node *lt;
    node *rt;
    node *par;
    Color color;
    int minPath;
};
node* findMin(node* nod);
node* findMax(node* nod);
node *insert(node* root, int key, node *prev);
struct node* deleteNode(struct node* root, int key);
int findMinPath(node *nod){
    if(nod == nullptr) return 0;
    nod->minPath=1+min(findMinPath(nod->lt), findMinPath(nod->rt));
    return nod->minPath;
}
bool color(node *root, int bl, int minPath){ // bl - left black nodes to use minPath- min distance to nearest null
    if(bl==-1) return false; // needed more black nodes than available
    if(root == nullptr) return true;
    if(root->minPath==minPath){ // node on the shortest path = must be black
        root->color=black;
        return ( color(root->lt, bl-1, minPath-1)&& color(root->rt, bl-1, minPath-1) );
    }
    else if(root->par->color==red){
        root->color=black;
        return ( color(root->lt, bl-1, minPath-1)&& color(root->rt, bl-1, minPath-1) );
    }
    else root->color=red;
    return ( color(root->lt, bl, minPath-1)&& color(root->rt, bl, minPath-1) );

}
bool colorRB(node *root){
    int height=findMinPath(root); // minimal dist to null from root, this will be the nr of black nodes on any path root-null
    root->color=black;
    return (color(root->lt, height-1, height-1) && color(root->rt, height-1, height-1));
}
main(){
    node *root=nullptr;
    root = insert(root, 3,nullptr);
    root = insert(root, 5,nullptr);
    root = insert(root, 2,nullptr);
    root = insert(root, 4,nullptr);
    root = insert(root, 6,nullptr);
    root = insert(root, 7,nullptr);
    root = insert(root, 8,nullptr);
    cout<<colorRB(root)<<endl;
    cout<<root->rt->color;
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
node *insert(node* root, int key, node *prev){
    if(root==nullptr) {
        root = new node;
        root->key=key;
        root->par=prev;
        root->lt=nullptr;
        root->rt=nullptr;
        root->color=black;
        root->minPath=-1;
        return root;
    }
    if (key < root->key)
        root->lt  = insert(root->lt, key, root);
    else if (key > root->key)
        root->rt = insert(root->rt, key, root);
    return root;
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
            struct node *temp = root->rt;
            delete root;
            return temp;
        }
        else if (root->rt == NULL){
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
