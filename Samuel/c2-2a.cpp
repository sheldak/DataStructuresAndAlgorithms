#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 100;

struct node{
    int val;
    node *next;
};

void add_end(node*& head, int el){

    node *p;
    node *current = head;
    p = new node;
    p->next = NULL;
    p->val = el;

    if(current != NULL){
        while(current->next != NULL)
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

void bucketSort(int A[N], int k){
    node **B=(node**)malloc(k*sizeof(node));

    for(int i=0; i<N; i++)
        add_end(B[A[i]/k], A[i]);

    for(int i=0; i<k; i++){
        insertSort(B[i]);
    }

    int y=0;
    for(int i=0; i<k; i++){
        while(B[i]!=nullptr) {
            A[y] = B[i]->val;
            B[i] = B[i]->next;
            y++;
        }
    }

}

void c2_2a(){
    srand(time(nullptr));

    int A[N];

    for(int i=0; i<N; i++) {
        A[i] = rand() % (N*N);
        cout << A[i] << " ";
    }
    cout<<endl;

    bucketSort(A, N);

    for(int i=0; i<N; i++)
        cout<<A[i]<<" ";
}