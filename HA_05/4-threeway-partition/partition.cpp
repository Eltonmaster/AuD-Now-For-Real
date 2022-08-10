#include<iostream>
#include<vector>
#include<algorithm>

std::vector<std::string> A;

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

// Hauptschleife
int main() {
    int n, a, b, p1,p2;
    while(std::cin >> n >> a >> b) {
        A.resize(n);
        for (std::string& s : A) {
            std::cin >> s;
        }
        partition(a, b, p1, p2);
        std::cout << p1 << " " << p2 << " :";
        for(const std::string& s : A) {
            std::cout << " " << s;
        }
        std::cout << std::endl;
    }
}