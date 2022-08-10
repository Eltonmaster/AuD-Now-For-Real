#include <iostream>

struct List {
    int value;
    List* next;
    ~List() {
        delete next;
    }
};

int main() {
    int size;
    while (std::cin >> size) {
        List* head = nullptr;
        while(size--) {
            int e;
            std::cin >> e;
            head = new List {e, head};
        }
        for (List* walker = head; walker!=nullptr; walker = walker->next) {
            std::cout << walker->value << (walker->next == nullptr ? '\n' : ' ');
        }
        delete head;
    }
}