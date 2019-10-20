#include <iostream>
#include <string>
#include "color.h"
#include "pair.hpp"

#define BAR (C_RED + std::string("-----------------------------------------------------------------") + C_NRM)

inline matf::pair<bool, std::string> read_data(const bool in_color = true)
{
    const std::string quote = 
        "Bez muke se pjesna ne ispoja\n"
        "bez muke se sablja ne sakova!\n"
        "Junastvo je car zla svakojega,\n"
        "a i pice najsladje dusevno,\n"
        "kojijem se pjane pokolenja.\n"
        "Blago tome ko dovijek zivi,\n"
        "imao se rasta i roditi!\n"
        "Vjecna zublja vjecne pomrcine,\n"
        "nit' dogori niti svjetlost gubi.\n\n";

    const std::string author = "           Petar Petrovic Njegos";

    return matf::make_pair(
        true,
        (in_color ? C_BLU : "")
            + quote
            + (in_color ? C_GRN : "")
            + author
            + (in_color ? C_NRM: "")
    );
}

int main()
{
    const auto p1 = read_data();

    if (p1.first) {
        std::cout << BAR << C_RED << "\nSADRZAJ:\n" << C_NRM << BAR << std::endl;
        std::cout << p1.second << '\n' << BAR << std::endl;
    } else {
        std::cout << C_RED << "Neuspesno procitana datoteka." << C_NRM << std::endl;
    }

    std::cout << "\n\nPrikaz kopiranja:" << std::endl;

    const auto p2(p1);
    matf::pair<bool, std::string> p3;
    p3 = p1;
    std::cout << p1.first << ", " << p1.second << std::endl;
    std::cout << p2.first << ", " << p2.second << std::endl;
    std::cout << p3.first << ", " << p3.second << std::endl;

    std::cout << "\n\nTestiranje razmene:" << std::endl;

    matf::pair<int, std::string> t1(1813, "Godina rodjenja");
    matf::pair<int, std::string> t2(1851, "Godina smrti");

    std::cout << "\n\n" << t1.first << ", " << t1.second << std::endl;
    std::cout << t2.first << ", " << t2.second << std::endl;

    t1.swap(t2);

    std::cout << "\n\n" << t1.first << ", " << t1.second << std::endl;
    std::cout << t2.first << ", " << t2.second << std::endl;

    // Strukturna dekompozicija (C++17) omogucava da i za nasu klasu
    // primenimo otpakivanje rezultata kao sto smo to cinili u prethodnim
    // primerima na vezbama za klasu std::pair.
    // Ovo je moguce usled toga sto su nam `first` i `second` clanovi
    // javni, odnosno slucaj 3:
    // https://en.cppreference.com/w/cpp/language/structured_binding
    std::cout << "\n\nTestiranje strukturne dekompozicije:" << std::endl;
    const auto [success, text] = read_data();
    if (success)
    {
        std::cout << text << std::endl;
    }

    return 0;
}
