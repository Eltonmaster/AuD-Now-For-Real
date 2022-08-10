#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int>& A) {
    /* Schritt 0: Trivialitätstest */
    int n = A.size();

    if (n==0) return 0; //Leerer Vector -> 0 
    if (n==1){
        if (A[0] <= 0) return 0;
        return A[0];
    };


    /* Schritt 1: Teile */
    int m = A.size()/2;
    const std::vector<int> Aleft (A.begin()  , A.begin()+m);
    const std::vector<int> Aright(A.begin()+m, A.end());

    /* Schritt 2: Rekursion */
    const int r1 = maxsum(Aleft);
    const int r2 = maxsum(Aright);

    /* Schritt 3: Kombiniere */
    int r31 = 0;
    int r = 0;
    for (int i=m-1; i>=0; i--){
        r+=A[i];
        if(r>=r31) r31=r;
    }
    int r32 = r = 0;
    for (int j=m; j<n; j++) {
        r += A[j];
        if (r>r32) r32 = r;
    }
    int r3 = r31+r32;

    if (r3 >= r2 && r3 >= r1) return r3;
    if (r2 >= r3 && r2 >= r1) return r2;
    if (r1 >= r3 && r1 >= r2) return r1;
    //return r3;
}

int main() {
    int size;
    while(std::cin >> size) {
        std::vector<int> v(size);
        for(int& x : v) std::cin >> x;
        std::cout << maxsum(v) << std::endl;
    }
}