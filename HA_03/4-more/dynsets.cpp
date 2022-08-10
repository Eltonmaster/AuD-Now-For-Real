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
        setACount(1);
        count = 0;
    }

    void setACount(word w){
        A.clear();
        for (word i = w; i>0; i--){
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

word powerOfTwo(word j) {       //2 hoch j
    word pow = 2;
    if (j == 0) pow = 1;
    else{
        for (word x = 1; x < j; x++){
            pow *= 2;
        }
    }
    return pow;
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
    word pow = powerOfTwo(k);
    return (S.A[j] & pow) != 0;
}

void insert(DynSets& S, word i) {
    if (!member(S,i)){
        S.count++;
        word j = i / w;
        word k = i % w;
        word pow = powerOfTwo(k);
        S.A[j] = S.A[j] | pow;
    }
    return;
}

void del(DynSets& S, word i) {
    if (member(S,i)){
        S.count--;
        word j = i / w;
        word k = i % w;
        word pow = powerOfTwo(k);
        S.A[j] = S.A[j] & (~pow);
    }
}

// DynSets-(Hilfs-)Operationen

word count(word i) {            //Bitweise vergleich ob bit in i gesetzt
    word c = 0;                 //Erhöhen des Counters c wenn ja
    while(i) {
        c += i & 1;
        i >>= 1;
    }
    return c;
}

DynSets uni(const DynSets& S, const DynSets& T) {
    DynSets U = empty(m);
    for (word i = 0; i < m; i++){
        U.A[i] = S.A[i] | T.A[i];
        for (word j = 0; j < w; j++){
            word pow = powerOfTwo(j);
            if ((U.A[i] & pow) != 0) U.count++;
        }
    }
    return U;
}

DynSets intersection(const DynSets& S, const DynSets& T) {
    DynSets U = empty(m);
    for (word i = 0; i < m; i++){
        U.A[i] = S.A[i] & T.A[i];
        for (word j = 0; j < w; j++){
            word pow = powerOfTwo(j);
            if ((U.A[i] & pow) != 0) U.count++;
        }
    }
    return U;
}

DynSets diff(const DynSets& S, const DynSets& T) {
    DynSets U = empty(m);
    for (word i = 0; i < m; i++){
        U.A[i] = S.A[i] & (~T.A[i]);
        for (word j = 0; j < w; j++){
            word pow = powerOfTwo(j);
            if ((U.A[i] & pow) != 0) U.count++;
        }
    }
    return U;
}

DynSets symdiff(const DynSets& S, const DynSets& T) {
    DynSets U = empty(m);
    for (word i = 0; i < m; i++){
        U.A[i] = S.A[i] ^ T.A[i];
        for (word j = 0; j < w; j++){
            word pow = powerOfTwo(j);
            if ((U.A[i] & pow) != 0) U.count++;
        }
    }
    return U;
}

DynSets comp(const DynSets& S) {
    DynSets T = empty(m);
    T.count = n - S.count;
    for(word i = 0; i < m; i++){
        T.A[i] = ~(S.A[i]);
    }
    if ((n % w) != 0)   T.A[m-1] = (T.A[m-1]) & (powerOfTwo(n % w)-1);


    return T;
}

// Weitere DynSets-Operationen

bool equal(const DynSets& S, const DynSets& T) {
    if (S.count != T.count || S.A.size() != T.A.size()) return false;
    for (word i=0; i<m; i++){
        if(toBinary(S.A[i]) != (toBinary(T.A[i]))) return false;
    }
    return true;
}

bool subset(const DynSets& S, const DynSets& T) {
    if (equal(S, T)) return true;

    DynSets P = empty(m);
    P = intersection(S, T);
    return equal(P, S);


    // for (word i=0; i<m; i++){
    //     if(S.A[i] > T.A[i]) return false;
    // }
    // return true;
}

bool disjoint(const DynSets& S, const DynSets& T) {
    DynSets U = empty(m);
    return equal(intersection(S,T), U);
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
            case 'x':                                   //index
            {
                        word a = id1/w;
                        word b = id1%w;
                        index(m, a, b);
                        break;
            }
            case 'm':   std::cin >> id2;                //member
                        std::cout << member(S[id1], id2) << std::endl;
                        break;
            case 'i':   std::cin >> id2;                //Insert
                        insert(S[id1], id2);
                        break;
            case 'd':   std::cin >> id2;                //Delete
                        del(S[id1], id2);
                        break;
            // DynSets-(Hilfs-)Operationen
            case 'h':   std::cin >> id2;                //Help? -> Count
                        std::cout << count(S[id1].A[id2]) << std::endl;
                        break;
            case 'u':   std::cin >> id2;         //union
                        std::cin >> id3;
                        S[id3] = uni(S[id1], S[id2]);
                        break;  
            case 't':   std::cin >> id2 >> id3;         //intersection
                        S[id3] = intersection(S[id1], S[id2]);
                        break;

            case 'f':   std::cin >> id2 >> id3;         //difference
                        S[id3] = diff(S[id1], S[id2]);
                        break;

            case 'y':   std::cin >> id2 >> id3;         //symmetric difference
                        S[id3] = symdiff(S[id1], S[id2]);
                        break;

            case 'o':   std::cin >> id2;         //complement
                        S[id2] = comp(S[id1]);
                        break;
            // Weitere DynSets-Operationen
            case 'q':   std::cin >> id2;        //equal test
                        std::cout << (equal(S[id1], S[id2])) << std::endl; 
                        break;

            case 's':   std::cin >> id2;        //subset test
                        std::cout << subset(S[id1], S[id2]) << std::endl; 
                        break;

            case 'j':   std::cin >> id2;        //disjoint test
                        std::cout << disjoint(S[id1], S[id2]) << std::endl; 
                        break;
        }   
    }
}