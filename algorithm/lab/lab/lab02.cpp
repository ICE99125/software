#include "lab.h"

double getPower(double x, int p) {
    if (p == 0) return 1.0;

    double res = getPower(x, p / 2);

    if (p % 2 != 0) {
        return res * res * x;
    }

    return res * res;
}

void lab02() {
    double base;

    std::cin >> base;

    int power;

    std::cin >> power;

    std::cout << std::fixed << std::setprecision(2) << getPower(base, power);
}