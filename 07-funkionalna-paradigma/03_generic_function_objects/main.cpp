#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class value_gte 
{
public:
    value_gte(const int comp)
        : m_comp(comp)
    {}

    template <typename ValType>
    bool operator() (ValType &&value) const 
    {
        // O referencama, kategorijama izraza i savrsenom prosledjivanju:
        // http://bajamircea.github.io/coding/cpp/2016/04/07/move-forward.html
        return std::forward<ValType>(value) >= m_comp;
    }

private:
    int m_comp;
};


int main()
{
    const value_gte gte42(42);

    std::cout << " 6 >= 42 -> " << gte42(6)  << std::endl;
    std::cout << "42 >= 42 -> " << gte42(42) << std::endl;

    const std::vector<float> xs { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };

    std::cout << std::count_if(std::cbegin(xs), std::cend(xs), gte42)
              << std::endl;
}
