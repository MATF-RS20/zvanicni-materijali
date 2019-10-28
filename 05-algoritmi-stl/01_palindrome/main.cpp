// Zadatak: Za dati argument komandne linije ispitati da li je palindrom.

#include <iostream>
#include <algorithm>
#include <string>

bool is_palindrome(const std::string & str)
{
    // Proveravamo da li su dve kolekcije jednake.
    // Nedostaje provera da li obe kolekcije imaju isti broj elemenata
    // sto nije potrebno u ovom slucaju.
    return std::equal(str.cbegin(), str.cend(), str.crbegin());
}

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " rec" << std::endl;
        return 1;
    }

    std::cout << argv[1] <<
        (is_palindrome(argv[1]) ? " jeste ":" nije ")
        << "palindrom"
        << std::endl;

    return 0;
}
