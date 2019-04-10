#include <iostream>
#include <cmath>

using namespace std;

struct node{
    node *left;
    node *right;
    node *parent;
    int key;
    int left_children;
};


void insert(node *&p, node *q, int key) {
    if (p == nullptr) {
        p = new node;
        p->left = p->right = nullptr;
        p->key = key;
        p->parent = q;
        p->left_children = 0;
    } else if (key < p->key) {
        insert(p->left, p, key);
        p->left_children++;
    } else
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

node *maximum(node *p){
    while(p != nullptr && p->right != nullptr)
        p = p->right;

    return p;
}

void decrease_up(node *p){
    if(p != nullptr){
        while(p->parent != nullptr){
            if(p->parent->left == p)
                p->parent->left_children--;

            p = p->parent;
        }
    }
}

void erase(node *&p, int key){
    node *e = find(p, key);
    if(e != nullptr){
        decrease_up(e);
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
                    ch->left_children = e->left_children-1;

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
                    ch->left_children = e->left_children-1;

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
                cout<<p->key<<": "<<p->left_children;
                flag = true;
            }
            else if(p != nullptr){
                flag = true;
                cout<<", "<<p->key<<": "<<p->left_children;
            }
            else if(p == nullptr && level != 0)
                cout<<", #";

        }
        level++;
        leaves *= 2;
    }
    cout<<"}"<<endl;
}

node *find_ith(node *p, int i){
    if(p == nullptr)
        return nullptr;

    if(p->left_children >= i)               // result on the left
        return find_ith(p->left, i);

    if(p->left_children + 1 == i)           // found
        return p;

    if(p->right == nullptr)                 // result on the right
        return nullptr;
    else
        return find_ith(p->right, i - p->left_children - 1);
}

int which(node *p){
    if(p == nullptr)
        return 0;

    int res = p->left_children + 1;
    while(p->parent != nullptr){
        if(p->parent->right == p)
            res += p->parent->left_children + 1;

        p = p->parent;
    }
    return res;
}


void c6_1(){

    node *bst = nullptr;
    insert(bst, nullptr, 10);
    insert(bst, bst->parent, 4);
    insert(bst, bst->parent, 3);
    insert(bst, bst->parent, 7);
    insert(bst, bst->parent, 1);
    insert(bst, bst->parent, 5);
    insert(bst, bst->parent, 9);
    insert(bst, bst->parent, 16);
    insert(bst, bst->parent, 11);
    insert(bst, bst->parent, 15);
    insert(bst, bst->parent, 19);
    insert(bst, bst->parent, 17);
    insert(bst, bst->parent, 23);
    insert(bst, bst->parent, 21);

    print(bst);

    node *f = find_ith(bst, 5);
    cout<<f->key<<endl;
    cout<<which(f->parent)<<endl;

    erase(bst, 10);

    print(bst);
}