#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

const int N = 100;

struct leng{
    int x = 0; // do zliczania ile jest wyrazow o literze tej samej lub wczesniejszej w alfabecie
    int n = 0;      // do zliczania ile jest wyrazow o takiej samej literze
    string S[N] = {""};     // do przechowywania wyrazow o tej literze
};

void countingSort(string S[N], bool letters, int pos, int w){       // sortowanie wyrazow

    if(letters){                    // sortowanie po literach o indeksie pos
        int from = 0;
        while(S[from].size() - 1 < pos && from < w)
            from++;

        if(w-from - 1 > 0){
            string T[N];
            leng C[26];

            for(int i=0; i<26; i++) {
                C[i].x = 0;
                C[i].n = 0;
            }

            for(int i=from; i<w; i++) {
                C[S[i][pos] - 97].S[ C[S[i][pos] - 97].x ] = S[i];
                C[S[i][pos] - 97].x++;
                C[S[i][pos] - 97].n++;
            }

            for(int i=1; i<26; i++)
                C[i].x += C[i-1].x;

            for(int i=w-1; i>=from; i--)
                T[--C[S[i][pos] - 97].x] = C[S[i][pos] - 97].S[--C[S[i][pos] - 97].n];


            for(int i=from; i<w; i++)
                S[i] = T[i-from];
        }
    }
    else{       // sortowanie po dlugosci wyrazu
        string T[N] = {};
        leng C[N];

        for(int i=0; i<w; i++) {
            C[S[i].size()].S[ C[S[i].size()].x  ] = S[i];
            C[S[i].size()].x++;
            C[S[i].size()].n++;
        }

        for(int i=1; i<N; i++)
            C[i].x += C[i-1].x;

        for(int i=w-1; i>=0; i--)
            T[--C[S[i].size()].x] = C[S[i].size()].S[--C[S[i].size()].n];

        for(int i=0; i<w; i++)
            S[i] = T[i];
    }
}

void sort(string S[N], int w){
    countingSort(S, false, 0, w);   // dlugosc

    int maxx = (int) S[w-1].size()-1;

    for(int i=maxx; i>=0; i--){
        countingSort(S, true, i, w);    // litery
    }
}

void c3_4(){
    srand(time(nullptr));

    string S[N];

    int curr_len = 0;
    int words = 0;
    while(curr_len < N){
        int len = rand()%(N/8) + 1;
        if(len + curr_len > N)
            len = N-curr_len;

        for(int j=0; j<len; j++)
            S[words] += (char) (rand()%26 + 97);

        words++;
        curr_len += len;
    }

    cout<<"NOT SORTED"<<endl;

    for(int i=0; i<words; i++)
        cout<<S[i]<<endl;
    cout<<endl;
    sort(S, words);

    cout<<"SORTED"<<endl;

    for(int i=0; i<words; i++)
        cout<<S[i]<<endl;
}