#include <iostream>
#include <cmath>
using namespace std;

struct node{
    node *left;
    node *right;
    node *parent;
    int key;
};


void insert(node *&p, node *q, int key){
    if(p == nullptr){
        p = new node;
        p->left = p->right = nullptr;
        p->key = key;
        p->parent = q;
    }
    else if(key < p->key)
        insert(p->left, p, key);
    else
        insert(p->right, p, key);
}

node *find(node *p, int key){
    while(p != nullptr && p->key != key){
        if(key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    return p;
}

node *minimum(node *p){
    while(p != nullptr && p->left != nullptr)
        p = p->left;

    return p;
}

node *maximum(node *p){
    while(p != nullptr && p->right != nullptr)
        p = p->right;

    return p;
}

node *next(node *p){    // minimum value in the tree which is higher than that given
    if(p->right != nullptr)
        return minimum(p->right);

    node *q = p->parent;
    while(q != nullptr && q->right == p){
        p = q;
        q = q->parent;
    }

    return q;           // if it is the maximum value in the tree, it returns nullptr;
}

void erase(node *&p, int key){
    node *e = find(p, key);
    if(e != nullptr){
        node *ch = maximum(e->left);
        if(ch == nullptr){                     // no elements on the left side
            if(e->right != nullptr){            // elements on the right side
                ch = e->right;
                ch->parent = e->parent;
                if(e->parent == nullptr)         // erasing the root
                    p = ch;
                else if(e->parent->left == nullptr || e->parent->left != e)     // erasing right child
                    e->parent->right = ch;
                else                                                            // erasing left child
                    e->parent->left = ch;
            }
            else{                               // no elements on the right side
                if(e->parent == nullptr)        // erasing last node
                    p = ch;
                else if(e->parent->left == nullptr || e->parent->left != e)     // erasing right child
                    e->parent->right = ch;
                else                                                            // erasing left child
                    e->parent->left = ch;
            }

            delete e;
        }
        else{               // elements on the left side
            if(e->left == ch){      // element to change with is the left child of that to erase
                ch->parent = e->parent;
                ch->right = e->right;
                if(ch->right != nullptr)
                    ch->right->parent = ch;

                if(e->parent == nullptr)           // erasing the root
                    p = ch;
                else if(e->parent->right == e)     // erasing right child
                    e->parent->right = ch;
                else                               // erasing left child
                    e->parent->left = ch;

                delete e;
            }
            else{
                if(ch->left == nullptr){    // element to change with has no children
                    ch->right = e->right;
                    ch->left = e->left;

                    ch->parent->right = nullptr;

                    ch->parent = e->parent;

                    if(e->parent == nullptr)           // erasing the root
                        p = ch;
                    else if(e->parent->right == e)     // erasing right child
                        e->parent->right = ch;
                    else                               // erasing left child
                        e->parent->left = ch;

                    delete e;
                }
                else{                       // element to change with has left child
                    ch->right = e->right;

                    ch->left->parent = ch->parent;
                    ch->parent->right = ch->left;
                    ch->left = e->left;

                    if(e->parent == nullptr)        // erasing the root
                        p = ch;
                    else if(e->parent->left == nullptr || e->parent->left != e)     // erasing right child
                        e->parent->right = ch;
                    else                                                            // erasing left child
                        e->parent->left = ch;

                    delete e;
                }

            }
        }
    }
}

void print(node *tree){
    int level = 0;
    int leaves = 1;
    cout<<"{";
    bool flag = true;
    node *p;
    while(flag){
        flag = false;
        if(level >= 1)
            cout<<"|";
        for(int i=1; i<=leaves; i++){
            int curr = (int) pow(2, level) + i -1;
            int curr_lvl = level;
            p = tree;

            while(p != nullptr && curr_lvl>=1){
                if(((int) (curr/pow(2,curr_lvl-1))) % 2 == 0)
                    p = p->left;
                else
                    p = p->right;

                curr_lvl--;
            }

            if(p != nullptr && level == 0){
                cout<<p->key;
                flag = true;
            }
            else if(p != nullptr){
                flag = true;
                cout<<", "<<p->key;
            }
            else if(p == nullptr && level != 0)
                cout<<", #";
        }
        level++;
        leaves *= 2;
    }
    cout<<"}"<<endl;

}

void c6_BST(){
    node *bst = nullptr;
    insert(bst, nullptr, 5);
    insert(bst, bst->parent, 2);
    insert(bst, bst->parent, 7);
    insert(bst, bst->parent, 0);
    insert(bst, bst->parent, 4);
    insert(bst, bst->parent, 3);

    print(bst);

    node *f = minimum(bst);
    cout<<f->key<<endl;
    cout<<next(f)->key<<endl;

    erase(bst, 5);

    print(bst);

}
