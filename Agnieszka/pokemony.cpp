#include <iostream>
using namespace std;
struct Node{
    int id;
    Node *next;
};
struct Pokemon{
    Node *hunters;
    int id;
    bool released;
    int left; // nr of pokemons left to be released in order to release this pokemon
};
struct HuntingList{
    HuntingList *next;
    int predator;
    int prey;
};
HuntingList* createHuntingList(int *l, int n);
void addNode(Node *&head, int id){
    Node *n = new Node;
    n->id = id;
    n->next = head;
    head = n;
}
int release(int id, int *relOrder, int relInd, Pokemon *pokemons){
    cout<<"releasing "<<id<<endl;
    pokemons[id].released=true;
    relOrder[relInd++] = id;
    Node *it = pokemons[id].hunters;
    while(it!=NULL){
        pokemons[it->id].left--;
        if(pokemons[it->id].left <=0 && !pokemons[it->id].released) release(it->id, relOrder, relInd, pokemons);
        it=it->next;
    }
    return relInd;
}
int* releaseThemAll(HuntingList *lista, int n){
    Pokemon *pokemons = new Pokemon[n];
    int *relOrder = new int[n];
    int relInd = 0;
    for(int i=0;i<n;i++) {
        pokemons[i].left=0;
        pokemons[i].released = false;
        pokemons[i].hunters = NULL;
    }
    while(lista!=NULL){
        pokemons[lista->predator].left=2;
        addNode(pokemons[lista->prey].hunters, lista->predator);
        lista = lista->next;
    }
    for(int i=0;i<n;i++){
        if(pokemons[i].left<=0 && !pokemons[i].released)
            relInd = release(i, relOrder, relInd, pokemons);
    }
    if(relInd < n) return NULL;
    return relOrder;
}

main(){
    int hList[] = { 0, 1, 0, 3, 2, 4, 2, 5, 4, 1, 4, 3};
    HuntingList *lista = createHuntingList(hList, 12);
    int *res = releaseThemAll(lista, 6);

}
HuntingList* createHuntingList(int *l, int n){
        HuntingList *h = NULL;
        for(int i=0;2*i<n;i++){
            HuntingList *tmp= new HuntingList;
            tmp->predator = l[2*i];
            tmp->prey = l[2*i+1];
            tmp->next = h;
            h=tmp;
        }
        return h;
}
