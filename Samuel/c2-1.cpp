#include <iostream>
using namespace std;

struct node{
    int val;
    node *next;
};

void add_end(node*& head, int el){  // dodawanie na koniec

    node *p;
    node *current = head;
    p = new node;
    p->next = nullptr;
    p->val = el;
    if(current != nullptr){
        while(current->next != nullptr)
            current = current->next;

        current->next = p;
    }
    else
        head = p;
}

node *partition(node *&p, node *&r){
    node *x = r;
    node *k = nullptr;

    if(r->next != nullptr)
        k = r->next;

    r->next = nullptr;

    node *it = p;
    while(it->next != x){
        if(it->next->val > x->val){
            node *tmp = it->next;
            r->next = tmp;
            it->next = it->next->next;
            r = r->next;

            tmp->next = nullptr;
        }
        else
            it = it->next;
    }

    r->next = k;

    return it;
}

void quickSort(node *p, node *r){
    if(p != r && p->next  != r){
        node *piv = partition(p, r);
        quickSort(p, piv);
        quickSort(piv, r);
    }
}

void qs(node *&h){
    node *w = new node;
    w->next = h;
    h = w;
    node *b = h;
    while(b != nullptr && b->next != nullptr)
        b = b->next;

    quickSort(h, b);

    h = h->next;
    delete w;
}

void c2_1(){

    node *first;
    first = new node;
    first = nullptr;

    add_end(first, 1);
    add_end(first, 11);
    add_end(first, 9);
    add_end(first, 1);
    add_end(first, 6);
    add_end(first, 8);
    add_end(first, 9);
    add_end(first, 2);
    add_end(first, 13);
    add_end(first, 7);
    add_end(first, 13);

    // ----- WYPISYWANIE -----
    node *current = first;
    if(current != nullptr) {
        cout << "{" << current->val;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->val << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->val << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;

    qs(first);

    current = first;
    if(current != nullptr) {
        cout << "{" << current->val;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->val << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->val << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;
}