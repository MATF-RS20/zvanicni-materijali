// Zadatak: Dat je vektor celih brojeva od 1 do 15.
// Transformisati vektor tako da oni brojevi koji pri deljenju brojem 3:
//   a) daju ostatak 0 idu na pocetak vektora (prva grupa),
//   b) daju ostatak 1 idu nakon prve grupe (druga grupa),
//   c) daju ostatak 2 idu nakon druge grupe (treca grupa).

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

bool div_by_3_remainder_0(const int x)
{
    return x % 3 == 0;
}

bool div_by_3_remainder_1(const int x)
{
    return x % 3 == 1;
}

int main(int argc, char *argv[])
{
    std::vector<int> xs { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    // Izdvajamo elemente koji su deljivi brojem 3 na pocetak kolekcije.
    // Algoritam vraca iterator na prvi element koji nije deljiv nakon razdvajanja.
    const auto first_end =
        std::stable_partition(std::begin(xs), std::end(xs), div_by_3_remainder_0);

    // Particionisemo ostatak kolekcije (preskacemo elemente koji su deljivi brojem 3).
    // Druga grupa ce imati samo elemente koji daju ostatak 1 pri deljenju brojem 3,
    // dok su elementi iz intervala [second_end, std::end(xs)) u trecoj grupi.
    const auto second_end =
        std::stable_partition(first_end, std::end(xs), div_by_3_remainder_1);

    std::copy(std::begin(xs), std::end(xs),
              std::ostream_iterator<int>(std::cout, " "));

    return 0;
}
