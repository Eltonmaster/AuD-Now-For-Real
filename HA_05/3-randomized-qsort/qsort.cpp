#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

std::vector<std::string> A;
std::default_random_engine gen;


int wuerfel(int a, int b){
    std::uniform_int_distribution<int> verteilung(a, b);
    return verteilung(gen);
}

// partition mit dem globalen Array A
// Aufruf partition(a,b,p) soll A[a..b] mit Pivot A[a] partitionieren
// und Zielposition des Pivotelements über p zurückgeben.
void partition(const int a, const int b, int& p) {
    /* Nach Voraussetzung gilt: 0 <= a < b <= A.size()-1 = n-1 */
    std::string x = A[a];
    int i = a+1;
    int j = b;
    while(i <= j) {
        while(i <= j && (A[i] <= x)) i++;
        while(j > i && (A[j] > x)) j--;
        if (i == j) j--;
        if (i < j) {
            std::swap(A[i], A[j]);
            i++;
            j--;
        }
    }
    if (a < j) std::swap(A[a], A[j]);
    p = j;
    return;
}

// r_qsort mit dem globalen Array A
// Aufruf r_qsort(a,b) soll A[a..b] sortieren!
void r_qsort(const int a, const int b) {
    if (a < b) {
        int s = wuerfel(a, b);
        int p;
        std::swap(A[a], A[s]);
        partition(a, b, p);
        r_qsort(a, p-1);
        r_qsort(p+1, b);
    }
}

// Hauptschleife
int main() {
    int n;
    while(std::cin >> n) {
        A.resize(n);
        for (std::string& s : A) {
            std::cin >> s;
        }
        r_qsort(0, n-1);
        if(n > 0) {
            std::cout << A[0];
            for(int i = 1; i < (int)A.size(); ++i) {
                std::cout << " " << A[i];
            }
        }
        std::cout << std::endl;
    }
}