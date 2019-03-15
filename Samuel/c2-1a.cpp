#include <iostream>
using namespace std;

struct node{
    int val;
    node *next;
};

struct list{
    node *start;
    node *last;
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

void add(list &l, node *n){

    node *k = new node;
    k->val = n->val;
    k->next = nullptr;

    if(l.start == nullptr){
        l.start = k;
        l.last = l.start;
    }
    else{
        l.last->next = k;
        l.last = l.last->next;
    }
}

list con(list l1, list l2, list l3){
    if(l1.start == nullptr){
        if(l2.start == nullptr)
            return l3;
        else
            l2.last->next = l3.start;

        l2.last = l3.last;
        return l2;
    }

    if(l2.start == nullptr) {
        l1.last->next = l3.start;
        l1.last = l3.last;
    }
    else{
        l1.last->next = l2.start;
        if(l3.start != nullptr) {
            l2.last->next = l3.start;
            l1.last = l3.last;
        }
        else
            l1.last = l2.last;
    }

    return l1;
}

list quickSort(list l){
    if(l.start == nullptr || l.start == l.last)
        return l;

    list l1, l2, l3;

    l1.start = l2.start = l3.start = nullptr;
    l1.last = l2.last = l3.last = nullptr;

    int x = l.start->val;

    node *r = l.start;

    while(r != nullptr){
        if(r->val < x)
            add(l1, r);
        else if(r->val == x)
            add(l2, r);
        else
            add(l3, r);

        r = r->next;
    }

    return con(quickSort(l1), l2, quickSort(l3));
}


void c2_1a(){

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

    list l;
    l.start = first;

    node *r = first;
    while(r != nullptr && r->next != nullptr)
        r = r->next;

    l.last = r;

    // ----- WYPISYWANIE -----
    node *current = l.start;
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

    l = quickSort(l);

    current = l.start;
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