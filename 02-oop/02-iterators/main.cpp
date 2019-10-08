#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

// Iteratori nam pruzaju apstrakciju nad pokazivacima.

int main()
{
    std::vector<int> xs;

    // Koriscenje std::copy algoritma za citanje i pisanje je
    // efikasno, ali neuobicajeno. Dodato je u primer samo
    // kao demonstracija nivoa apstrakcije koju iteratori
    // prave nad pokazivacima u C-u.
    // Iteratore cemo intenzivno koristiti kada budemo koristili
    // algoritme standardne biblioteke.

    // Na primer, ucitavanje celih brojeva sa standardnog ulaza!
    std::copy(
        std::istream_iterator<int>(std::cin),
        std::istream_iterator<int>(),
        // std::back_inserter je pogodna funkcija koja za datu kolekciju
        // konstruise iterator koji se koristi za dodavanje elemenata na kraj te kolekcije.
        // Ocigledno, ovo funkcionise samo za one kolekcije koje imaju definisanu operaciju push_back.
        std::back_inserter(xs)
    );

    // Sortiramo vektor, osim prvog i poslednjeg elementa
    std::sort(xs.begin() + 1, xs.end() - 1);
    // Alternativno, i preporuceno, je koristili std::begin i std::end
    // jer su opstiji (u ovom slucaju rade isto). Na primer, ukoliko je xs
    // staticki-alociran niz ili neka druga kolekcija (koja podrzava operacije begin i end), 
    // sledeci kod bi i dalje radio.
    // std::sort(std::begin(xs) + 1, std::end(xs) - 1);

    // Ispisujemo sadrzaj 
    std::copy(xs.cbegin(), xs.cend(), std::ostream_iterator<int>(std::cout, " , "));
    // Alternativno, i preporuceno, kao i sa sortiranjem vektora iznad
    // jeste koriscenje funkcija std::cbegin i std::cend za dobijanje
    // konstantnih iteratora na pocetak, odnosno, kraj kolekcije.
    // std::copy(std::cbegin(xs), std::cend(xs), std::ostream_iterator<int>(std::cout, " , "));
    std::cout << std::endl;

    // Ispisujemo sadrzaj u obrnutom poretku
    std::copy(xs.crbegin(), xs.crend(), std::ostream_iterator<int>(std::cout, " , "));
    // Ponovo, kao i u prethodnim slucajevima,
    // preporucuje se koriscenje std::rbegin, std::rend, std::crbegin, std::crend funkcija.
    // std::copy(std::crbegin(xs), std::crend(xs), std::ostream_iterator<int>(std::cout, " , "));

    return 0;
}
