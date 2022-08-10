#include <iostream>
#include <stack>

int main() {
    int size;
    while(std::cin >> size) {
        std::stack<int> s;
        while (size--) {
            int e;
            std::cin >> e;
            s.push(e);
        }
        while (!s.empty())
        {
            std::cout << s.top();
            s.pop();
            std::cout << (s.empty() ? '\n' : ' ');
        }
        
    }
}
