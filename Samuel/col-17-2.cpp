/* Proszę zaimplementować funkcję:
int SumBetween(int T[], int from, int to, int n);
Zadaniem tej funkcji jest obliczyć sumę liczb z n elementowej tablicy T, które w posortowanej
tablicy znajdywałyby się na pozycjach o indeksach od from do to (włącznie). Można przyjąć, że
liczby w tablicy T są parami różne (ale nie można przyjmować żadnego innego rozkładu danych).
Zaimplementowana funkcja powinna być możliwie jak najszybsza. Proszę oszacować jej złożoność
czasową (oraz bardzo krótko uzasadnić to oszacowanie).
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(int T[], int p, int r, int s){
    swap(T[s], T[r]);

    int piv = T[r];
    int j = p-1;

    for(int i=p; i<r; i++){
        if(T[i] < piv){
            j++;
            swap(T[i], T[j]);
        }
    }
    swap(T[j+1], T[r]);
    return j+1;
}

int select(int T[], int p, int r, int i){       // szukamy i-tego najmniejszego elementu
    if(p == r)
        return T[p];

    int s = rand()%(r-p+1) + p;     // pivot dla partition

    int q = partition(T, p, r, s);

    int k = q-p+1;

    if(k == i)
        return T[q];
    else if(k < i)
        return select(T, q+1, r, i-k);
    else
        return select(T, p, q-1, i);
}

int sumBetween(int T[], int from, int to, int n){
    int fromValue = select(T, 0, n-1, from);       // indeks elementu najmniejszego ktory dodajemy
    int toValue = select(T, 0, n-1, to);           // indeks elementu najwiekszego ktory dodajemy


    int sum = 0;
    for(int i=0; i<n; i++){
        if(T[i] >= fromValue && T[i] <= toValue)
            sum += T[i];
    }
    return sum;
}

void c17_2(){
    srand(time(nullptr));

    int n = 10;
    int *T;
    T = new int[n];

    for(int i=0 ;i<n; i++){
        T[i] = rand()%(n*10);       // gdy nie dziala to przez to ze jest kilka takich samych liczb
        cout<<T[i]<<" ";
    }
    cout<<endl<<endl;

    cout<<sumBetween(T, 1, 3, n);

}