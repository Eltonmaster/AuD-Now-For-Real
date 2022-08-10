#include <iostream>

struct Point {
    int x;
    int y;
};

int main() {
    Point p1, p2;
    char c;

    while(1) {
        std::cin >> c >> p1.x >> c >> p1.y >> c >> c >> p2.x >> c >> p2.y >> c;
        if (!std::cin.good()){
            break;
        }
        std::cout << '(' << p1.x+p2.x << ',' << p1.y+p2.y << ')' << std::endl;
        }



}
