#include <angle/angle.hpp>
#include <iostream>
#include <cmath>

int main() {
    constexpr ang::degrees d{90};
    constexpr ang::radians r = ang::to_radians(d);

    std::cout << d << "  =  " << r << '\n';
    std::cout << "sin(90°) = " << std::sin(r) << '\n';

    constexpr ang::radians sum = r + r;
    std::cout << "2·90° = " << ang::to_degrees(sum) << '\n';
}