#include <iostream>

using namespace std;

const int MAX = 16; // 1048576;

struct element{
    string key;
    bool full;
    bool erased;
};

int hashing(string key){        // changing key to index
    int n = key.size();
    int fnk = 0;
    int curr = n-1;
    n--;

    while(n>=0){
        fnk += (int) key[curr] - 96;

        if(n>=1)
            fnk += 26*((int) key[curr-1] - 96);

        if(n>=2)
            fnk += 26*26*((int) key[curr-2] - 96);

        if(n>=3)
            fnk += 26*26*26*((int) key[curr-3] - 96);

        if(n>=4)
            fnk += 26*26*26*26*((int) key[curr-4] - 96);

        curr-=4;
        n-=4;
    }
    return fnk%MAX;
}

void insert(element T[], string key){
    int i = 0;
    bool inserted = false;
    int h = hashing(key);
    while(!inserted){
        if(!T[(h+i*i)%MAX].full){
            T[(h+i*i)%MAX].key = key;
            T[(h+i*i)%MAX].full = true;
            T[(h+i*i)%MAX].erased = true;
            inserted = true;
        }
        i++;
    }
}

bool search(element T[], string key){
    int h = hashing(key);
    if(T[h].erased){
        if(T[h].full && T[h].key == key)
            return true;

        int i=1;
        while((h+i*i)%MAX != h && T[(h+i*i)%MAX].erased){
            if(T[(h+i*i)%MAX].full && T[(h+i*i)%MAX].key == key)
                return true;
            i++;
        }
    }
    return false;
}

void erase(element T[], string key){
    int h = hashing(key);
    bool erased = false;

    if(T[h].erased){
        if(T[h].full && T[h].key == key){
            T[h].key = "";
            T[h].full = false;
            erased = true;
        }

        int i=1;
        while(!erased && (h+i*i)%MAX != h && T[(h+i*i)%MAX].erased){
            if(T[(h+i*i)%MAX].full && T[(h+i*i)%MAX].key == key){
                T[(h+i*i)%MAX].key = "";
                T[(h+i*i)%MAX].full = false;
                erased = true;
            }
            i++;
        }
    }
}

void reorganise(element T[]){
    element tmp[MAX];

    for(int i=0; i<MAX; i++){
        tmp[i].full = false;
        tmp[i].erased = false;
    }

    for(int i=0; i<MAX; i++){
        if(T[i].full){
            int h = hashing(T[i].key);
            insert(tmp, T[i].key);
        }
    }

    for(int i=0; i<MAX; i++){
        T[i] = tmp[i];
    }
}

void print(element T[]){
    for(int i=0; i<MAX; i++){
        if(i==0)
            cout<<"{";

        if(T[i].key == "")
            cout<<"#";
        else
            cout<<T[i].key;

        if(i<=MAX-2)
            cout<<", ";
        else
            cout<<"}";
    }
    cout<<endl;
}

void c5_hashMap(){
    element T[MAX];

    for(int i=0; i<MAX; i++) {
        T[i].key = "";
        T[i].full = false;
        T[i].erased = false;

    }

    bool quit = false;
    while(!quit){
        cout<<"---HASH MAP---"<<endl;
        cout<<"options:"<<endl;
        cout<<"i - insert"<<endl;
        cout<<"e - erase"<<endl;
        cout<<"f - find"<<endl;
        cout<<"p - print"<<endl;
        cout<<"r - reorganise"<<endl;
        cout<<"q - quit"<<endl;

        string s;
        cin>>s;

        if(s == "i"){
            cout<<"how many?"<<endl;
            int n;
            cin>>n;
            for(int i=0; i<n; i++){
                string p;
                cin>>p;
                insert(T, p);
            }
        }
        else if(s == "e"){
            cout<<"how many?"<<endl;
            int n;
            cin>>n;
            for(int i=0; i<n; i++){
                string p;
                cin>>p;
                erase(T, p);
            }
        }
        else if(s == "f"){
            string p;
            cin>>p;
            if(search(T, p))
                cout<<"found";
            else
                cout<<"not found";
            cout<<endl;
        }
        else if(s == "p")
            print(T);
        else if(s == "r") {
            reorganise(T);
            cout<<"reorganised"<<endl;
        }
        else if(s == "q")
            quit = true;
        else
            cout<<"invalid character"<<endl;

        cout<<endl;
    }
}