#include <iostream>
#include "Fraction.hpp"

int main()
{
    Fraction r(0, 1);

    std::cin >> r;

    std::cout << "Unet je razlomak: " << r << std::endl;

    std::cout << "r++: " << r++ << std::endl;
    std::cout << "++r: " << ++r << std::endl;

    std::cout << "r: " << r << std::endl;

    // Implicitno kastovanje u double
    double d1 = r;
    std::cout << "implicitno (double)r = " << d1 << std::endl;

    // Eksplicitno C kastovanje u double
    double d2 = (double)r;
    std::cout << "eksplicitno (double)r = " << d2 << std::endl;

    // Preporuceno kastovanje u C++ svetu koristeci static_cast.
    // https://stackoverflow.com/questions/103512/why-use-static-castintx-instead-of-intx
    double d3 = static_cast<double>(r); 
    std::cout << "static_cast<double>(r) = " << d3 << std::endl;

    std::cout << Fraction(-3, 2) << std::endl;

    Fraction tmp = Fraction(1, 1) - Fraction(2, 1);
    std::cout << "-1/1 == " << tmp << std::endl;

    return 0;
}
