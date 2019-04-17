#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct node{
    node *left;
    node *right;
    node *parent;
    int key;
    bool colour;        // false - BLACK; true - RED
    int left_dist;
    int right_dist;
};


void dist(node *p){
    if(p->left == nullptr && p->right == nullptr){
        p->left_dist = 0;
        p->right_dist = 0;
    }
    else {
        if (p->left != nullptr) {
            dist(p->left);
            p->left_dist = max(p->left->left_dist, p->left->right_dist) + 1;
        } else
            p->left_dist = 0;


        if (p->right != nullptr) {
            dist(p->right);
            p->right_dist = max(p->right->left_dist, p->right->right_dist) + 1;
        } else
            p->right_dist = 0;
    }
}

bool colour(node *p, int blacks){
    if(p->parent == nullptr)
        p->colour = false;

    if(p->left == nullptr && p->right == nullptr)
        return true;

    if(p->left_dist * 2 + 1 < p->right_dist || p->right_dist * 2 + 1 < p->left_dist)
        return false;


    if(p->left_dist == p->right_dist){
        if(blacks == 0){
            p->left->colour = true;
            p->right->colour = true;
        }
        else{
            p->left->colour = false;
            p->right->colour = false;
        }

    }else if(p->left_dist > p->right_dist){
        if(blacks == 0){
            p->left->colour = !p->colour;

            if(p->right != nullptr)
                p->right->colour = false;
        }else{
            p->left->colour = false;

            if(p->right == nullptr)
                return false;
            else
                p->right->colour = false;
        }

    }else{
        if(blacks == 0){
            p->right->colour = !p->colour;

            if(p->left != nullptr)
                p->left->colour = false;
        }else{
            p->right->colour = false;

            if(p->left == nullptr)
                return false;
            else
                p->left->colour = false;
        }

    }
    bool x;
    bool y = true;
    if(p->left_dist == p->right_dist){
        x = colour(p->left, 0);
        y = colour(p->right, 0);
    }
    else if(p->left_dist > p->right_dist){
        x = colour(p->left, max(blacks-1, 0));
        if(p->right != nullptr)
            y = colour(p->right, max(p->left_dist/2 - 1, blacks-1));
        else{
            if(max(p->left_dist/2 - 1, blacks-1) > 0)
                return false;
        }
    }
    else{
        x = colour(p->right, max(blacks-1, 0));
        if(p->left != nullptr)
            y = colour(p->left, max(p->right_dist/2 - 1, blacks-1));
        else{
            if(max(p->right_dist/2 - 1, blacks-1) > 0)
                return false;
        }
    }

    return x&&y;

}

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
                cout<<", "<<p->key<<": "<<p->left_dist<<","<<p->right_dist;
            }
            else if(p == nullptr && level != 0)
                cout<<", #";
        }
        level++;
        leaves *= 2;
    }
    cout<<"}"<<endl;

}

void c7_1(){
    node *bst = nullptr;
    insert(bst, nullptr, 5);
    insert(bst, bst->parent, 2);
    insert(bst, bst->parent, 7);
    insert(bst, bst->parent, 0);
    insert(bst, bst->parent, 4);
    insert(bst, bst->parent, 3);
    dist(bst);
    print(bst);
}