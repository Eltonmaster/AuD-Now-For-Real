#include <iostream>
#include <cstdint>
#include <vector>
#include <unordered_map>

using word = uint64_t;
const word w = 64;
word n, m;

struct DynSets {
    std::vector<word> A;
    word count;
    DynSets() {
        A.clear();
        count = 0;
    }

    void setACount(word w){
        A.clear();
        for (word i = w; w>0; w--){
            A.push_back(0);
        }
    }
};

std::unordered_map<word,DynSets> S;

// Hilfsoperationen

void printDecimal(const DynSets& S) {
    std::cout << '(';
    word i = S.A.size();
    while(i-- > 1) std::cout << S.A[i] << ',';
    if(i == 0) std::cout << S.A[0];
    std::cout << ") " << S.count << std::endl;
}

std::string toBinary(word x) {
    std::string s = "";
    for(word i = 0; i < w; ++i) {
        s = ((x & 1) ? "1" : "0") + s;
        x >>= 1;
    }
    return s;
}

void printBinary(const DynSets& S) {
    std::cout << '(';
    word i = S.A.size();
    while(i-- > 1) std::cout << toBinary(S.A[i]) << ',';
    if(i == 0) std::cout << toBinary(S.A[0]);
    std::cout << ") " << S.count << std::endl;
}

// Einfache Operationen

DynSets empty(word m) {
    DynSets D = DynSets();
    D.setACount(m);
    return D;
}

bool isempty(const DynSets& S) {
    return (S.count == 0);
}

word card(const DynSets& S) {
    return S.count;
}

// Hauptprogramm

int main() {
    // Setup
    std::cin >> n;
    m = (n + w-1) / w;
    // Hauptschleife
    char command;
    word id1;
    while(std::cin >> command >> id1) {
        switch(command) {
            // Einfache Operationen
            case 'p':   printDecimal(S[id1]);
                        break;
            case 'b':   printBinary(S[id1]);
                        break;
            case 'n':   S[id1] = empty(m);
                        break;
            case 'e':   std::cout << isempty(S[id1]) << std::endl;
                        break;
            case 'c':   std::cout << card(S[id1]) << std::endl;
                        break;
        }
    }
}