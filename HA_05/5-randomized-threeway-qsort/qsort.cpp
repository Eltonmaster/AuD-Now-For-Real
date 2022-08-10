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
// Aufruf partition(a,b,p1,p2) soll A[a..b] mit Pivot A[a] partitionieren
// und Bereichsgrenzen über p1 und p2 zurückgeben.
void partition(const int a, const int b, int& p1, int& p2) {
    /* Nach Voraussetzung gilt: 0 <= a < b <= A.size()-1 = n-1 */
    std::string x = A[a];
    int i = a;
    int j = a+1;
    int k = b;

    while(j <= k) {
        if (A[j] < x) {
            std::swap(A[j], A[i]);
            i++;
            j++;
        } else if (A[j] > x) {
            if (j!=k) std::swap(A[j], A[k]);
            k--;
        } else {
            j++;
        }
    }
    p1 = i;
    p2 = k;
}

// r_qsort mit dem globalen Array A
// Aufruf r_qsort(a,b) soll A[a..b] sortieren!
void r_qsort(const int a, const int b) {
    if (a < b) {
        int s = wuerfel(a, b);
        int p1;
        int p2;
        std::swap(A[a], A[s]);
        partition(a, b, p1, p2);
        r_qsort(a, p1-1);
        r_qsort(p2+1, b);
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