#include <iostream>
#include <cassert>

int alive = 0;

struct List {
    int value;
    List* next;
    List(int v = 0, List* n = nullptr) : value(v), next(n) {
        alive++;
    }
    ~List() {
        delete next;
        alive--;
    }
};

int main() {
    List* head = nullptr;
    int x, y;
    while(std::cin >> x >> y){
        if(!head) {
            head = new List{y, nullptr};
        } else {
            List* walker = head;
            while(walker->next && walker->value != x)
                walker = walker->next;
            walker->next = new List{y, walker->next};
        }
        for(List* walker = head; walker; walker = walker->next) {
            std::cout << walker->value << (walker->next == nullptr ? '\n' : ' ');
        }
    }
    delete head;
    assert(alive == 0);
}