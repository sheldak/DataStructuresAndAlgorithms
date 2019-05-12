/*
Student chce wypuścić n różnych pok´emonów (numerowanych od 0 do n − 1) z klatek
        (pok´eball’i). Wypuszczony Pok´emon natychmiast atakuje swojego wybawiciela, chyba że (a) jest
        spokojny, lub (b) w okolicy znajdują się co najmniej dwa uwolnione pok´emony, na które ten
        pok´emon poluje. Proszę zaimplementować funkcję:
int* releaseThemAll( HuntingList* list, int n ),
        gdzie list to lista z informacją, które pok´emony polują na które (lista nie zawiera powtórzeń):
struct HuntingList {
    HuntingList* next; // następny element listy
    int predator; // numer pokemona, który poluje
    int prey; } // numer pokemona, na którego poluje
        Funkcja powinna zwrócić n elementową tablicę z numerami pok´emonów w kolejności
wypuszczania (tak, żeby wypuszczający nie został zaatakowany) lub NULL jeśli taka kolejność nie
istnieje. Każdy wypuszczony pok´emon zostaje ”w okolicy”. Jeśli pok´emon nie występuje na liście
        jako predator to znaczy, że jest spokojny. Zaimplementowana funkcja powinna być możliwie jak
najszybsza. Proszę krótko oszacować jej złożoność.*/


#include <iostream>
using namespace std;

struct HuntingList {
    HuntingList* next;
    int predator;
    int prey;
};

struct edge{
    int v;
    edge *next;
};

HuntingList *add_to_list(HuntingList *list, int predator, int prey){
    HuntingList *n = new HuntingList;
    n->predator = predator;
    n->prey = prey;
    n->next = list;
    list = n;

    return list;
}

void add_edge(edge **graph, HuntingList *list){
    edge *n = new edge;
    n->v = list->predator;
    n->next = graph[list->prey];
    graph[list->prey] = n;

}

void release(edge **graph, int *predators, int n, int *res, int *curr_res){
    if(predators[n] == 0){
        res[*curr_res] = n;
        *curr_res = *curr_res + 1;

        predators[n] = -1;
        while(graph[n] != nullptr){
            predators[graph[n]->v]--;
            release(graph, predators, graph[n]->v, res, curr_res);
            graph[n] = graph[n]->next;
        }
    }
}

int* releaseThemAll( HuntingList* list, int n ){
    int *res = new int[n];
    int curr_res = 0;
    int *curr = &curr_res;
    int *predators = new int[n];
    for(int i=0; i<n; i++) predators[i]=0;

    edge *graph[n];

    for(int i=0; i<n; i++){
        graph[i] = nullptr;
    }

    while(list != nullptr){
        add_edge(graph, list);
        predators[list->predator] = 2;
        list = list->next;
    }

    for(int i=0; i<n; i++)
        release(graph, predators, i, res, curr);

    if(curr_res < n)
        return nullptr;

    return res;
}

void c16_1(){
    HuntingList *list = nullptr;
    int n = 6;

    list = add_to_list(list, 0, 1);
    list = add_to_list(list, 0, 3);
    list = add_to_list(list, 1, 2);
    list = add_to_list(list, 1, 4);
    list = add_to_list(list, 2, 3);
    list = add_to_list(list, 2, 5);
    list = add_to_list(list, 4, 2);
    list = add_to_list(list, 4, 5);

    int *res;
    res = releaseThemAll(list, n);

    if(res == nullptr)
        cout<<"NULL";
    else{
        for(int i=0; i<n; i++)
            cout<<res[i]<<" ";
    }
}