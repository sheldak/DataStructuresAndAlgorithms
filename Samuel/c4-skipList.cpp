#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getLevel(int max_level){
    int lvl=0;

    while(rand()%10 < 5 && lvl < max_level)
        lvl++;

    return lvl;
}

// --- SkipList ---

struct SLNode{
    int key;
    SLNode** next;

    SLNode(int key, int level);
};

SLNode::SLNode(int key, int level) {
    this->key = key;
    next = new SLNode *[level + 1];

    for (int i = 0; i < level + 1; i++)
        next[i] = nullptr;
}


struct SkipList{
    SLNode* first;
    int max_level;

public:
    SkipList(int max_level);
    SLNode* createNode(int key, int level);
    void insert(int key);
    SLNode *find(int key);
    void print();
};

SkipList::SkipList(int max_level) {
    this->max_level = max_level;
    first = new SLNode(-1, max_level);
}

SLNode* SkipList::createNode(int key, int level) {
    SLNode *n = new SLNode(key, level);
    return n;
}

void SkipList::insert(int key){
    SLNode *p = first;

    for(int lvl=max_level-1; lvl >= 0; lvl--){
        while(p->next[lvl] != nullptr && key > p->next[lvl]->key)
            p = p->next[lvl];
    }

    if(p->next[0] == nullptr || p->next[0]->key != key){
        p = first;

        int lvl = getLevel(max_level);
        SLNode *n = createNode(key, max_level);

        for(; lvl >= 0; lvl--){

            while(p->next[lvl] != nullptr && key > p->next[lvl]->key)
                p = p->next[lvl];

            n->next[lvl] = p->next[lvl];
            p->next[lvl] = n;
        }
    }
}

SLNode* SkipList::find(int key){
    SLNode *p = first;

    for(int lvl = max_level - 1; lvl >= 0; lvl--){
        while(p->next[lvl] != nullptr && key > p->next[lvl]->key)
            p = p->next[lvl];
    }

    p = p->next[0];

    if(key == p->key)
        return p;

    return nullptr;
}

void SkipList::print(){
    for(int lvl=max_level; lvl>=0; lvl--){
        SLNode *p = first;
        while(p != nullptr) {
            cout << p->key << " ";
            p = p->next[lvl];
        }
        cout<<endl;
    }
}

void c4_skipList(){
    srand(time(nullptr));

    int max_level = 5;

    SkipList *SL = new SkipList(max_level);

    SL->insert(3);
    SL->insert(17);
    SL->insert(22);
    SL->insert(6);
    SL->insert(11);
    SL->insert(1);
    SL->insert(9);
    SL->insert(16);
    SL->insert(4);
    SL->insert(14);
    SL->insert(11);
    SL->insert(10);
    SL->insert(19);
    SL->insert(5);
    SL->insert(8);
    SL->insert(21);

    SL->insert(9);

    SL->print();

    SLNode *f = SL->find(9);
    cout<<endl<<f->key;
}