#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int>& A) {
    int best = 0;
    int n = A.size();
    int i = 0, t = 0;

    for (int j=0; j<n; j++){
        t += A[j];
        if (t<0) {
            i = j+1;
            t = 0;
        }
        if (t>best) {
            best = t;
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