// Primer koji ilustruje erase-remove idiom:
// https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // Stanje vektora na pocetku:
    // 1 - 2 - 3 - 2 - 5 - 2 - 6 - 2 - 4 - 8 - X
    // |                                       |
    // Begin                                   End
    vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};

    // Idiomatsko brisanje elemenata iz vektora se vrsi u 2 koraka:

    // 1. "Pomeramo" sve elemente "2" koriscenjem std::remove algoritma na kraj vektora.
    // Ovi elementi nece zaista biti pomereni
    // vec ce se preostali elementi organizovati
    // tako da njihov poredak bude korektan.
    const auto new_end (remove(begin(v), end(v), 2));
    // Nakon ovog poziva, stanje vektora je sledece:
    // 1 - 3 - 5 - 6 - 4 - 8 - 6 - 2 - 4 - 8 - X
    // |                       |               |
    // Begin                   NewEnd          End

    // 2. "Uklanjamo" sve elemente od "novog" kraja do kraja vektora.
    // Metod erase ce pozvati destruktor elemenata koji se nalaze nakon kraja.
    v.erase(new_end, end(v));
    // Nakon ovog poziva, stanje vektora je sledece:
    // 1 - 3 - 5 - 6 - 4 - 8 - X - X - X - X
    // |                       |
    // Begin                   End

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << endl;

    // Uklanjamo sve neparne elemente
    const auto odd = [](int i) { return i % 2 != 0; };
    // Erase-remove(_if) idiom u jednoj liniji:
    v.erase(remove_if(begin(v), end(v), odd), end(v));
    // Nakon ovog poziva, stanje vektora je sledece:
    // 6 - 4 - 8 - X - X - X - X - X - X - X
    // |           |
    // Begin       End

    // Smanjujemo kapacitet vektora sa pocetnog (10)
    // na onaj broj elemenata koji je preostao.
    // Moze doci do realokacije.
    v.shrink_to_fit();
    // Nakon ovog poziva, stanje vektora je sledece:
    // 6 - 4 - 8 - X
    // |           |
    // Begin       End

    for (auto i : v) {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}