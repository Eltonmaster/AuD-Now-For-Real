#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int size;
    std::cin >> size;
    std::vector<int> vec(size);
    for(int i = 0; i < size; i++){
        std::cin >> vec[i];
    }
    int i, j;
    while(std::cin >> i >> j) {
        int r = vec[i];
        for(int k = i+1; k<j; k++) {
            r = std::min(r, vec[k]);
        }
        std::cout << r << std::endl;
    }
}