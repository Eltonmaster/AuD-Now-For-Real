#include <iostream>
#include <cassert>

int living = 0;
struct Tree {
    Tree* left;
    int key;
    Tree* right;
    Tree(Tree* l, int k, Tree* r) : left(l), key(k), right(r) {
        ++living;
    }
    ~Tree() {
        delete left; delete right;
        --living;
    }
};

std::ostream& operator<<(std::ostream& out, const Tree* T) {
    if (!T)
        return out << "-";
    else
        return out << "(" << T->left << "," << T->key << "," << T->right << ")";
}

bool lookup(const Tree* T, const int key) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,nullptr}; // T == (-,2,-)
     * bool b = lookup(T, 4); // T == (-,2,-), b == false
     */
    
    if (T==nullptr) return false;
    if (T->key == key) return true;
    if (key < T->key){
        return lookup(T->left, key);
    } else {
        return lookup(T->right, key);
    }
}

Tree* insert(Tree* T = nullptr, const int key=-1) {
    /*
     * Verwendung:
     * Tree* T = nullptr; // T == -
     * T = insert(T, 2);  // T == (-,2,-)
     * T = insert(T, 4);  // T == (-,2,(-,4,-))
     */
    
    if (T==nullptr){
        Tree* newT = new Tree(nullptr, key, nullptr);
        return newT;
    }
    if (T->key == key) return T;                                    //wenn key schon in Tree

    if (key < T->key && T->left == nullptr) {                       //linke Seite
        T->left = insert(T->left, key);
    }
    if (key < T->key && T->left != nullptr) return insert(T->left, key);
    
    if (key > T->key && T->right == nullptr) {                       //rechte Seite
        T->right = insert(T->right, key);
    }
    if (key > T->key && T->right != nullptr) return insert(T->right, key);

}

int main() {
    char c; int key;
    Tree* T = nullptr;
    while(std::cin >> c >> key) {
        switch (c)
        {
        case 'i':
            if (T==nullptr) {T = insert(T, key);}
            else {insert(T, key);}
            std::cout << T << std::endl;
            break;

        case 'l':
            std::cout << (lookup(T,key) ? "1" : "0") << std::endl;
            break;
        
        default:
            std::cout << "Input not in the right format" << std::endl;
            break;
        }
    }
    delete T; T = nullptr;
    assert(!living);
}