#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

std::vector<std::string> A;

// partition mit dem globalen Array A
// Aufruf partition(a,b,p) soll A[a..b] mit Pivot A[a] partitionieren
// und Zielposition des Pivotelements über p zurückgeben.
void partition(const int a, const int b, int& p) {
    /* Nach Voraussetzung gilt: 0 <= a < b <= A.size()-1 = n-1 */
    std::string x = A[a];
    int i = a+1;
    int j = b;
    int temp;
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



// Hauptschleife
int main() {
    int n, a, b, p;
    while(std::cin >> n >> a >> b) {
        A.resize(n);
        for (std::string& s : A) {
            std::cin >> s;
        }
        partition(a, b, p);
        std::cout << p << " :";
        for(const std::string& s : A) {
            std::cout << " " << s;
        }
        std::cout << std::endl;
    }
}