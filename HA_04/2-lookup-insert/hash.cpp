#include<iostream>
#include<vector>
#include<iterator>

template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
    out << '(';
    if(!v.empty()) {
        std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(out, ","));
        out << v.back();
    }
    return out << ')';
}

const std::string EMPTY   = "",  /* kommen nie als Schlüssel vor */
                  DELETED = "-";

std::vector<std::string> table;
int tableSize;

const int p = 16777259;
const std::vector<std::uint64_t> a = {
    5902272, 7629265, 5333771,12383661,11774175,
    9802969,12640503, 3201625,16072600, 3335533,
    5101852,    3440,13405035,12903727,13147288,
    1825828,16182670,12801869, 8007159, 2376172,
};

int linHash(const std::string& s) {
    std::int64_t num = 0;
    for(int i = 0; i < s.size(); i++){
        num+= int(s[i])*a[i];
    }
    return num % 16777259;
}

bool lookup(const std::string& s) {
    int value = linHash(s);
    int position = value%tableSize;
    for(int i = 0; i < tableSize; i++){
        std::string temp = table[(position+i)%tableSize];
        if (temp == s) return true;
        if (temp == EMPTY) return false;
    }
    return false;
}

void insert(const std::string& s) {
    int value = linHash(s);
    int position = value%tableSize;
    bool jump = false;
    int temp;
    for (int i = 0; i < table.size(); i++){
        std::string tempCalc = table[(position+i)%tableSize];
        if (tempCalc == s) return;
        if (tempCalc == DELETED){
            if (!jump){
                temp = (position+i)%tableSize;
                jump = true;
            }
            continue;
        } 
        if (tempCalc == EMPTY){
            if (jump){
                table[temp] = s;
                return;
            }
            table[(position+i)%tableSize] = s;
            return;
        } 
    }
    return;
}

void _delete(const std::string& s) {
    int value = linHash(s);
    int position = value%tableSize;
    for (int i = 0; i < tableSize; i++){
        if (table[(position+i)%tableSize] == s){
            table[(position+i)%tableSize] = DELETED;
            return;
        }
        if (table[(position+i)%tableSize] == EMPTY) return;
    }
}

int main() {
    size_t size; std::cin >> size;
    /* erzeuge Tabelle der Groesse size, jeder Eintrag ist EMPTY */
    table.resize(size,EMPTY);
    tableSize = table.size();
    char c; std::string s;
    while(std::cin >> c >> s) {
        switch (c)
        {
        case 'h':   std::cout << "h("<< s <<") = " << linHash(s) << std::endl;
            break;
        
        case 'p':   std::cout << table << std::endl;
            break;

        case 'l':   std::cout << lookup(s) << std::endl;
            break;

        case 'i':   insert(s);
            break;

        case 'd':   _delete(s);
        
        default:
            break;
        }
    }
}