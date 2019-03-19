#include <iostream>
#include <algorithm>
using namespace std;
const int N=10;

main(){
    int A[N];
    int cnt=0;
    int max_ind=0;
    /**
    we iterate over a given array keeping counter cnt - if A[i] value is diff than A[i-1] value we decrement cnt by 1, otherwise we increment
    if cnt == 0 we change the candidate = max_ind to current index and set cnt at 1; if majority el exists it will be the one at max_ind.
        we then iterate again over the array and check if the candidate occurs in fact more than n/2 times;
    **/
}
