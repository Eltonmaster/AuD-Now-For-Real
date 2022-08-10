#include <iostream>
#include "fibonacci.h"

int main() {
    int x;
    while(std::cin >> x) {
        std::cout<< fib(x) << std::endl;
    }
}