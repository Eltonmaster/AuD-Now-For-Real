#ifndef __FIBONACCI_H_INCLUDED__
#define __FIBONACCI_H_INCLUDED__

#include <cstdint>

std::int64_t fib(int i) {
    if (i==0) {return 0;}
    if (i==1) {return 1;}

    std::int64_t pre1 = 1;
    std::int64_t pre2 = 0;
    std::int64_t curr;

    for (int j = 2; j<=i; j++) {
        curr = pre1 + pre2;
        pre2 = pre1;
        pre1 = curr;
    }

    return curr;
}

#endif // __FIBONACCI_H_INCLUDED__