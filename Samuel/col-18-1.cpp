#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 5;

struct Pupil{
    int group;
    Pupil *next;
};

void add_end(Pupil *& head, int gr){  // dodawanie na koniec

    Pupil *p;
    Pupil *current = head;
    p = new Pupil;
    p->next = nullptr;
    p->group = gr;
    if(current != nullptr){
        while(current->next != nullptr)
            current = current->next;

        current->next = p;
    }
    else
        head = p;
}

int distanceToIdeal(Pupil *L){
    if(N == 0)
        return 0;

    int ind_sum = 0;
    for(int i=0; i<2*N; i++){
        if(L->group == 0)
            ind_sum += i;

        L = L->next;
    }

    return 2*(ind_sum - (0 + N-1) * N / 2);     // suma indeksow zielonych (0) musi byc rowna sumie c. aryt. od 0 do N-1
                                                // musza przejsc tyle indeksow o ile wiecej od tej sumy wynosi ich
                                                // aktualna suma indeksow, niebiescy przechodza tyle samo
}

void c18_1(){
    srand(time(nullptr));

    Pupil *first = nullptr;

    int zero = 0;
    int one = 0;
    for(int i=0; i<2*N; i++) {
        int x = rand()%2;
        if((x == 0 && zero < N) || (x == 1 && one == N)) {
            add_end(first, 0);
            zero++;
        }
        else{
            add_end(first, 1);
            one++;
        }

    }

    // ----- WYPISYWANIE -----
    Pupil *current = first;
    if(current != nullptr) {
        cout << "{" << current->group;
        current = current->next;
        if(current == nullptr)
            cout<<"}"<<endl;
        else
            cout<<", ";

        while (current != nullptr && current->next != nullptr) {
            cout << current->group << ", ";
            current = current->next;
        }

        if(current != nullptr)
            cout << current->group << "}"<<endl;
    }
    else
        cout<<"{}"<<endl;

    cout<<distanceToIdeal(first);
}