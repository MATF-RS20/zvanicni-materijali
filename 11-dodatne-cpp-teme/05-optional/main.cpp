#include <iostream>
#include <optional>

using namespace std;

// Sablonska klasa `std::optional` nam sluzi za cuvanje vrednosti
// koje mogu, ali i ne moraju, biti izracunate.
// Na primer, funkcija `read_int` pokusava da procita ceo broj sa standardnog ulaza.
// Ukoliko uspe, vratice procitanu vrednost skladistenu u objektu klase `std::optional<int>`.
// Medjutim, ako ne uspe, vratice "neizracunati" (tj. prazan) `std::optional` objekat
// (sto se predstavlja kao `std::nullopt` vrednost).
optional<int> read_int()
{
    int i;
    if (cin >> i)
    {
        return {i};
    }
    return {};
}

// Predefinisemo `operator+` za dve "mozda celobrojne" vrednosti
optional<int> operator+(optional<int> a, optional<int> b)
{
    // Ukoliko bilo koja vrednost ne postoji,
    // vrati prazan `std::optional` objekat
    if (!a || !b)
    {
        return {};
    }
    // Inace, vrati `std::optional` objekat
    // koji sadrzi njihov zbir.
    return {*a + *b};
}

// Predefinisemo `operator+` za "mozda celobrojnu" vrednost i celi broj
optional<int> operator+(optional<int> a, int b)
{
    if (!a)
    {
        return {};
    }
    return {*a + b};
}

int main()
{
    cout << "Unesite 2 cela broja:" << endl;
    // Ukoliko korisnik nije uneo celi broj
    // pri unosu nekog od brojeva `a` ili `b`,
    // tada ce taj broj biti prazan `std::optional` objekat
    auto a = read_int();
    auto b = read_int();

    // Sabiranje uspeva samo ako postoje obe vrednosti `a` i `b`
    auto sum = a + b + 10;
    if (!sum)
    {
        cout << "Niste uneli 2 cela broja!" << endl;
        return -1;
    }

    cout << *a << " + " << *b << " + 10 = " << *sum << endl;

    return 0;
}