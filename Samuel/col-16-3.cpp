#include <iostream>
using namespace std;

struct Node{
    int value;
    Node *next;
};

void add_end(Node*& head, int el){  // pomocnicze do wypisywania

    Node *p;
    Node *current = head;
    p = new Node;
    p->next = nullptr;
    p->value = el;

    if(current != nullptr){
        while(current->next != nullptr)
            current = current->next;

        current->next = p;
    }
    else
        head = p;
}


Node *fixSortedList(Node *L){
    Node *w = new Node;         // wartownik
    w->next = L;
    L = w;

    Node *curr = L;

    while(curr->next->next != nullptr && curr->next->value < curr->next->next->value)
        curr = curr->next;

    if(curr->next->value > curr->next->next->value){

        if(curr->next->next->next == nullptr || curr->next->value < curr->next->next->next->value){     // jedna liczba
            Node *k = curr->next->next;                                                // zostala zmniejszona
            curr->next->next = curr->next->next->next;

            curr = L;

            while(curr->next->value < k->value)
                curr = curr->next;

            k->next = curr->next;
            curr->next = k;
        }
        else{           // liczba zostala zwiekszona
            Node *k = curr->next;
            curr->next= curr->next->next;

            while(curr->next != nullptr && curr->next->value < k->value)
                curr = curr->next;

            k->next = curr->next;
            curr->next = k;
        }

    }

    L = L->next;    // usuwanie wartownika

    delete w;
    return L;
}

void c16_3(){
    Node *first;
    first = new Node;
    first = nullptr;

    add_end(first, 61);
    add_end(first, 3);
    add_end(first, 7);
    add_end(first, 9);
    add_end(first, 12);
    add_end(first, 14);
    add_end(first, 16);
    add_end(first, 32);
    add_end(first, 34);
    add_end(first, 56);
    add_end(first, 60);

    // ----- WYPISYWANIE -----
    Node *current = first;
    if(current != nullptr) {
        cout << "{" << current->value;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->value << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->value << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;

    Node *newL = fixSortedList(first);

    current = newL;
    if(current != nullptr) {
        cout << "{" << current->value;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->value << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->value << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;
}
