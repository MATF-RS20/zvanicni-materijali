#include <iostream>
#include <algorithm>

using namespace std;

// Klasa koja implementira iterator kroz cele brojeve
class num_iterator
{
    int i_;

public:
    explicit num_iterator(int i = 0)
        : i_{i}
    {}

    // Operatori dereferenciranja, inkrementiranja i razlicitosti
    // neophodni su nam da bismo mogli da koristimo klasu za kolekcijsku `for` petlju
    int operator*() const
    {
        return i_;
    }

    num_iterator& operator++()
    {
        ++i_;
        return *this;
    }

    bool operator!=(const num_iterator &other) const
    {
        return i_ != other.i_;
    }

    // Operator jednakosti nam je neophodan za algoritam `std::minmax_element`
    // koji pozivamo u `main` funkciji
    bool operator==(const num_iterator &other) const
    {
        return !(*this != other);
    }
};

// Takodje, da bi nasa klasa iteratora bila kompatibilna sa algoritmima STL,
// potrebno je da definisemo neka svojstva iteratora.
// To se navodi implementiranjem specijalizacije klase `std::iterator_traits` za nas iterator.
// U kodu ispod vidimo da za nas iterator vazi:
// 1. Pripada kategoriji iteratora "unapred"
// 2. Iterira kroz `int` vrednosti
namespace std {
    template <>
    struct iterator_traits<num_iterator> {
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
    };
}
// Svojstva iteratora (https://en.cppreference.com/w/cpp/iterator/iterator_traits):
// 1. Tip `difference_type` predstavlja tip izraza `it1 - it2`
// 2. Tip `value_type` predstavlja tip izraza `*it` (tip je `void` za ciste izlazne iteratore)
// 3. Tip `pointer` predstavlja tip koji pokazivac mora biti da bi mogao da pokazuje na element
// 4. Tip `reference` predstavlja tip koji referenca mora biti da bi mogla da referise na element
// 5. Tip `iterator_category` predstavlja kategoriju iteratora

// Pomocna klasa koju cemo koristiti u kolekcijskoj petlji
class num_range
{
    int from_;
    int to_;

public:
    num_range(int from, int to)
        : from_{from}
        , to_{to}
    {}

    // Atribut `[[nodiscard]]` sluzi da obelezi funkciju
    // cija povratna vrednost ne bi trebalo da bude odbacena.
    // Kompilatori bi trebalo da makar prijave upozorenje
    // ako se odbaci povratna vrednost ovako oznacenih funkcija.
    [[nodiscard]] num_iterator begin() const
    {
        return num_iterator{from_};
    }

    [[nodiscard]] num_iterator end() const
    {
        return num_iterator{to_};
    }
};

int main()
{
    num_range r{-5, 5};

    cout << "Sve vrednosti iz intervala:" << endl;
    for (auto i : r)
    {
        cout << i << ", ";
    }
    cout << endl;

    cout << "Najmanji i najveci element:" << endl;
    auto [min_it, max_it] = minmax_element(r.begin(), r.end());
    cout << "min: " << *min_it << ", max: " << *max_it << '\n';

    return 0;
}