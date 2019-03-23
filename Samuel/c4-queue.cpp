#include <iostream>
using namespace std;

struct stack{
    int size=6;
    int top=0;
    int *T;

public:
    stack();
    bool isEmpty();
    void put(int el);
    int pop();
};

bool stack::isEmpty(){
    return !top;
}

void stack::put(int el){
    if(top+1 > size){
        int *nT = nullptr;
        nT = new int[size*2];

        for(int i=0; i<size; i++)
            nT[i] = T[i];

        size*=2;

        T = nT;
    }

    T[top++] = el;
}

int stack::pop(){
    if(isEmpty()) {
        cout << "Stack is empty!"<<endl;
        return -1;
    }
    else{
        return T[--top];
    }
}

stack::stack() {
    size = 2;
    top = 0;
    T = new int[2];
}


struct queue{
    stack s1;
    stack s2;

public:
    void push(int el);
    int get();
};

void queue::push(int el){
    s2.put(el);
}

int queue::get(){
    if(s1.isEmpty()){
        if(s2.isEmpty()){
            cout<<"Queue is empty!"<<endl;
            return -1;
        }
        else{
            while(!s2.isEmpty())
                s1.put(s2.pop());
        }
    }
    return s1.pop();
}


void c4_queue(){
    queue Q;

    Q.push(3);
    Q.push(6);
    Q.push(7);
    Q.push(2);
    Q.push(7);
    Q.push(8);

    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
    cout<<Q.get()<<endl;
}