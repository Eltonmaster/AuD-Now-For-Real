#include <iostream>

int main() {
    long a, b;
    while (1) {
        std::cin >> a >> b;
        if (!std::cin.good()){
            break;
        }
        std::cout << a+b << std::endl;
    }
}
