#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> M(n, std::vector<int>(m));

    for(int i = 0; i < n; i++){
        for(int j = 0; j<m; j++) {
            std::cin >> M[i][j];
        }
    }
    int i1, j1, i2, j2;

    while(std::cin >> i1 >> j1 >> i2 >> j2) {
        int r = M[i1][j1];
        for(int i = i1; i< i2; i++){
            for(int j= j1; j<j2; j++){
                r = std::min(r, M[i][j]);
            }
        }
        std::cout << r << std::endl;
    }
}