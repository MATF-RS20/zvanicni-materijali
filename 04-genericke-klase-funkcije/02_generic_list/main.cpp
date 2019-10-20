#include "list.hpp"
#include <iostream>

int main()
{
    matf::list<int> xs; 

    xs.push_back(3);
    xs.push_back(4);
    xs.push_back(5);

    xs.push_front(2);
    xs.push_front(1);
    xs.push_front(0);

    std::cout << "xs: " << xs << std::endl;

    std::cout << "\nPrebacujemo iz xs u ys" << std::endl;

    auto ys = std::move(xs);
    std::cout << "xs: " << xs << std::endl; 
    std::cout << "ys: " << ys << std::endl;

    std::cout << "\nys.pop_front()" << std::endl;
    ys.pop_front();
    std::cout << "ys: " << ys << std::endl;
    
    std::cout << "\nxs = ys;" << std::endl;
    xs = ys;
    std::cout << "xs: " << xs << std::endl;
    std::cout << "ys: " << ys << std::endl;

    return 0;
}

