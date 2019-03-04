#include <iostream>
#include <algorithm>
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

void insertSort(node *&h){
    node *curr = h;

    while(curr != nullptr && curr->next != nullptr){
        node *p = curr->next;
        node *tmp = h;
        if(tmp->val > curr->next->val){
            curr->next = curr->next->next;
            p->next = h;
            h = p;
        }
        else{
            while(tmp->next->val < p->val)
                tmp = tmp->next;

            if(tmp->next != p){
                curr->next = curr->next->next;
                p->next = tmp->next;
                tmp->next = p;
            }
            else
                curr = curr->next;
        }
    }
}

void selectionSort(node *&h){
    node *curr = h;

    while(curr != nullptr && curr->next != nullptr){
        node *p = curr->next;
        node *minn = curr;
        while(p != nullptr){
            if(p->val < minn->val)
                minn = p;
            p = p->next;
        }
        swap(minn->val, curr->val);
        curr = curr->next;
    }

}

void listSort(){

    node *first;
    first = new node;
    first = nullptr;

    add_end(first, 7);
    add_end(first, 12);
    add_end(first, 1);
    add_end(first, 6);
    add_end(first, 9);
    add_end(first, 15);
    add_end(first, 22);
    add_end(first, 9);

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

    selectionSort(first);

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