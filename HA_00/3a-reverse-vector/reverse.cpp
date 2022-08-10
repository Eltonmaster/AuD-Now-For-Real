#include <iostream>
/* TODO */

int main() {
    int length;
    int temp;
    while (1) {
        std::cin >> length;
        int arr[length];
        if (!std::cin.good()){
            break;
        } 
        for (int i = length; i > 0; i--){
            std::cin >> temp;
            arr[i-1] = temp;
        }

        for (int i = 0; i < length; i++) {
            if (i == length-1) {
                std::cout << arr[i] << std::endl;
            } else {
                std::cout << arr[i] << ' ';
            }
        }
    }
}
