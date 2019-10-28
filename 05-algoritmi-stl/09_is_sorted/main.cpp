// Zadatak: Napisati sablonsku funkciju is_sorted koja za datu kolekciju
// proverava da li je sortirana neopadajuce.

#include <iostream>
#include <string>
#include <numeric>
#include <vector>

template <typename T>
bool less_than_or_equal(const T& left, const T& right)
{
    return left <= right;
}

bool conjunction(const bool left, const bool right)
{
    return left && right;
}

template <typename T,
          typename Inner = typename T::value_type>
bool is_sorted(const T& xs)
{
    return std::inner_product(std::begin(xs), std::end(xs) - 1,
                              std::begin(xs) + 1,
                              true,
                              conjunction,
                              less_than_or_equal<Inner>);
}

int main(int argc, char *argv[])
{
    const std::string text = "Hooloovoo";
    std::cerr << text << ": " << is_sorted(text) << std::endl;

    const std::string word = "Almost";
    std::cerr << word << ": " << is_sorted(word) << std::endl;

    const std::vector<int> numbers{ 1, 2, 3, 3, 4, 5, 6, 6, 7 };
    std::cerr << "numbers: " << is_sorted(word) << std::endl;

    return 0;
}


