#include <iostream>
#include <vector>
#include <algorithm>

struct Sum {
    int i,j,s;
};

std::ostream& operator<<(std::ostream& s, const Sum& x) {
    return s << "(" << x.i << "," << x.j << "," << x.s << ")";
}

bool operator<(const Sum& x, const Sum& y) {
    if (&x==&y) return false;
    if (y.s>x.s) return true;
    if (y.s == x.s) {
        if (y.i <= x.i && y.j <= x.j) return true;
    }
}

Sum maxsum(const std::vector<int>& A) {
    Sum best {0,-1,0};
    int i = 0, t = 0;
    int n = A.size();

    for (int j=0; j<n; j++){
        t += A[j];
        if (t<0) {
            i = j+1;
            t = 0;
        }
        if (t>best.s) {
            best = {i, j, t};
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