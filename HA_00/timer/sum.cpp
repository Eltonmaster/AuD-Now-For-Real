#include <iostream>
#include "Timer.h"

uint64_t sum(int n) {
    uint64_t s = 0;
    for(int i = 1; i <= n; ++i) {
        s += i;
    }
    return s;
}

int main() {
    int n;
    Timer t;
    while(std::cin >> n) {
        t.start();
        uint64_t s = sum(n);
        t.stop();
        std::cout << s << std::endl;
        std::clog << "n = " << n << std::endl
                  << t.getTime() << std::endl;
    }
}