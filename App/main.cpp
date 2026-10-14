#include <iostream>
#include "PolyUtils.h"

int main() {
    double p[] = { 1, 2, 3 };          // 1 + 2x + 3x^2
    double q[] = { 0, 1 };             // x
    double r[10];

    int n = PolyAdd(p, 3, q, 2, r, 10);
    std::cout << "add: n=" << n << ", r[1]=" << r[1] << "\n";   // 3

    n = PolyMultiply(p, 3, q, 2, r, 10);
    std::cout << "mul: n=" << n << "\n";                         // 4

    double v;
    PolyEvaluate(p, 3, 2.0, &v);
    std::cout << "p(2)=" << v << "\n";                           // 17

    n = PolyDerivative(p, 3, r, 10);
    std::cout << "deriv n=" << n << ", r[0]=" << r[0] << "\n";   // 2, 2

    n = PolyIntegral(p, 3, 0.0, r, 10);
    std::cout << "integral n=" << n << "\n";                     // 4

    // Граничні випадки
    std::cout << "nullptr:   " << PolyAdd(nullptr, 3, q, 2, r, 10) << "\n"; // -1
    std::cout << "n=0:       " << PolyAdd(p, 0, q, 2, r, 10) << "\n";       // -2
    std::cout << "buffer error: " << PolyMultiply(p, 3, q, 2, r, 2) << "\n";   // -3
}