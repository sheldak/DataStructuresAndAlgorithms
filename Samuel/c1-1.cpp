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

void mergeSort(node *&h, node *&start, int len){
    if(len == 0 || len == 1)
        return;

    if(len == 2){                                       // gdy tylko 2 elementy
        if(start->next->val > start->next->next->val){
            node *tmp = start->next->next;
            start->next->next = start->next->next->next;
            tmp->next = start->next;
            start->next = tmp;
        }
    }
    else{
        int len1 = (len+1)/2;       // dlugosci 2 podlist
        int len2 = len - len1;

        mergeSort(h, start, len1);      // sortowanie pierwszej podlisty

        node *start2 = start;
        for(int i=0; i<len1; i++)
            start2 = start2->next;

        mergeSort(h, start2, len2);     // sortowanie drugiej podlisty

        node *start1 = start;
        for(int i=0; i<len; i++){       // laczenie 2 podlist
            if((len2 > 0 && start1->next->val > start2->next->val) || len1 <= 0){
                node *tmp = start2->next;
                start2->next = start2->next->next;
                tmp->next = start1->next;
                start1->next = tmp;

                len2--;
                start1 = start1->next;
            }
            else {
                len1--;
                start1 = start1->next;
            }
        }
    }
}


void c1_1() {

    node *first;
    first = new node;
    first = nullptr;

    add_end(first, 17);
    add_end(first, 12);
    add_end(first, 1);
    add_end(first, 6);
    add_end(first, 9);
    add_end(first, 15);
    add_end(first, 22);
    add_end(first, 9);

    // ----- WYPISYWANIE -----
    node *current = first;
    if (current != nullptr) {
        cout << "{" << current->val;
        current = current->next;
        if (current == nullptr)
            cout << "}" << endl;
        else
            cout << ", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->val << ", ";
            current = current->next;
        }

        if (current != nullptr)
            cout << current->val << "}" << endl;
    } else
        cout << "{}" << endl;

    node *w = new node;     // wartownik
    w->next = first;
    first = w;

    node *tmp=w;
    int len=0;
    while(tmp->next != nullptr){
        len++;
        tmp = tmp->next;
    }
    tmp = nullptr;
    delete tmp;
    cout<<len;
    mergeSort(first, first, len);

    w = first;
    first = first->next;
    delete w;

    // ----- WYPISYWANIE -----
    current = first;
    if (current != nullptr) {
        cout << "{" << current->val;
        current = current->next;
        if (current == nullptr)
            cout << "}" << endl;
        else
            cout << ", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->val << ", ";
            current = current->next;
        }

        if (current != nullptr)
            cout << current->val << "}" << endl;
    } else
        cout << "{}" << endl;

}