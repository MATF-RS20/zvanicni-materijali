#include "list.hpp"

#include <iostream>

int main()
{
    std::cout << "Pravimo listu xs..." << std::endl;

    matf::list xs;

    xs.push_back(3);
    xs.push_back(4);
    xs.push_back(5);

    xs.push_front(2);
    xs.push_front(1);
    xs.push_front(0);

    std::cout << "XS: " << xs << std::endl;

    std::cout << "Izbacujemo prvi element iz xs..." << std::endl;
    
    xs.pop_front();

    std::cout << "XS: " << xs << std::endl;

    std::cout << "Kopiramo podatke iz xs u ys..." << std::endl;

    auto ys = xs;

    std::cout << "XS: " << xs << std::endl;
    std::cout << "YS: " << ys << std::endl;
   
    std::cout << "Prebacujemo podatke iz ys u zs..." << std::endl;

    // S obzirom da smo "ukrali" implementaciju ys,
    // u opstem slucaju ne bi trebalo da je koristimo u daljem kodu.
    // Ipak, mi ispisujemo njen sadrzaj da bismo pokazali da
    // operator dodele sa semantikom pomeranja 
    // zaista "krade" implementaciju iz ys.
    const auto zs = std::move(ys);

    std::cout << "XS: " << xs << std::endl;
    std::cout << "YS: " << ys << std::endl;
    std::cout << "ZS: " << zs << std::endl;

    return 0;
}