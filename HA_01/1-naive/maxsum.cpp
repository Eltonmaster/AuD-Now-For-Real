#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int>& A) {
    int best = 0;    //Angleichen an Übungsaufgabe   
    int best_i = 0;  //Nicht verwendet jedoch in Übungsaufgabe
    int best_j = -1; 
    int n = A.size();

    for(int i=0; i < n; i++) {
        int s=0;
        for(int j=i; j<n; j++) {
            s+=A[j];
            if (s>best) {best=s; best_i=i; best_j=j;}
        }
    }
    return best;
}

int main() {
    int size;
    while(std::cin >> size) {
        std::vector<int> v(size);
        for(int& x : v) std::cin >> x;
        std::cout << maxsum(v) << std::endl;
    }
}