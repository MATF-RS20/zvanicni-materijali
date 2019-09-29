#include <iostream>
#include <vector>
#include <complex>
#include <numeric>

int main()
{
    std::vector<std::complex<double>> numbers;
    std::complex<double> number;

    // Citamo dok je ulaz validan
    // za std::complex na primer: (1,2) (3,4) ...
    while (std::cin >> number) {
        numbers.push_back(number);
    }

    // Prikaz sadrzaja vektora
    for (const auto& n: numbers) {
        std::cout << n << std::endl;
    }

    const auto sum = std::accumulate(numbers.cbegin(), numbers.cend(), std::complex<double>());

    std::cout << "Aritmeticka sredina: " << sum / std::complex<double>(numbers.size()) << std::endl;

    return 0;
}
