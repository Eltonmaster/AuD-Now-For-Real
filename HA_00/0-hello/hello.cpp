#include <string>
#include <iostream>

int main() {
    std::string s;
    std::cout << "enter name: ";
    std::cin >> s;
    std::cout << "Hello " << s << "!" << std::endl; 
    return 0;
}