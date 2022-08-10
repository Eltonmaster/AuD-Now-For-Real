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
        setACount(0);
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

// DynSet-(Hilfs-)Operationen

void index(word i, word& j, word& k) {
    std::cout << j << ' ' << k << std::endl;
}

bool member(const DynSets& S, word i) {
    word j = i / w;
    word k = i % w;
    word pow = 2;

    if (k == 0) pow = 1;
    else {
        for (word x = 1; x < k; x++){
            pow *= 2;
        }
    }
    return (S.A[j] & pow) != 0;
}

void insert(DynSets& S, word i) {
    if (!member(S,i)){
        S.count++;
        word j = i / w;
        word k = i % w;
        word pow = 2;     

        if (k == 0) pow = 1;
        for (word x = 1; x < k; x++){
            pow *= 2;
        }
        S.A[j] = S.A[j] | pow;
    }
    return;
}

void del(DynSets& S, word i) {
    if (member(S,i)){
        S.count--;
        word j = i / w;
        word k = i % w;
        word pow = 2;

        if (k == 0) pow = 1;
        for (word x = 1; x < k; x++){
            pow *= 2;
        }
        S.A[j] = S.A[j] & (~pow);
    }
}

// Hauptprogramm

int main() {
    // Setup
    std::cin >> n;
    m = (n + w-1) / w;
    // Hauptschleife
    char command;
    word id1, id2, id3;
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
            // DynSet-(Hilfs-)Operationen
            case 'x':   
            {
                        word a = id1/w;
                        word b = id1%w;
                        index(m, a, b);
                        break;
            }
            case 'm':   std::cin >> id2;
                        std::cout << member(S[id1], id2) << std::endl;
                        break;
            case 'i':   std::cin >> id2;
                        insert(S[id1], id2);
                        break;
            case 'd':   std::cin >> id2;
                        del(S[id1], id2);
                        break;
        }
    }
}