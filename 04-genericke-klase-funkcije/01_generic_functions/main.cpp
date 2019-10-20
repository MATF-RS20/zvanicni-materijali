#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "point.hpp"

#define THE_BAR "-------------------------------------------------------------------------"
#define TITLED_BAR(msg) std::cout << THE_BAR << "\n" << msg << "\n" << THE_BAR << std::endl

// "C"-ovski nacin da se napise "genericka funkcija"
// kroz koriscenje sistema zasnovanog na makroima.
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// Da li sledeci kod validno radi?
// int main() {
//    int a = 1, b = 2;
//    printf ("%d\n", MAX(a, b));
//    printf ("a=%d, b=%d\n\n", a, b);
//
//    printf ("%d\n", MAX(a++, b++));
//    printf ("a=%d, b=%d\n\n", a, b);
//}

namespace matf {

// Sablonska funkcija koja vraca maksimum od dve prosledjene vrednosti.
// Vrednosti mogu biti bilo kog tipa nad kojima je definisan operator '>'.
// Kljucna rec `inline` sugerise kompilatoru da pokusa da 
// poziv funkcije zameni direktno sa implementacijom funkcije. 
// Time se moze izbeci cena pozivanja funkcije.
template <typename T>
inline T max(T a, T b)
{
    return a > b ? a : b;
}

// Funkcija `iota` (inspirisano sa `std::iota`) inicijalizuje
// elemente prosledjene kolekcije podataka na value, ++value, ...
template <typename ForwardIterator, typename T>
void iota(ForwardIterator begin, ForwardIterator end, T value)
{
    while (begin != end)
    {
        *begin++ = value++;
    }
}

// Funkcija `max_element` vraca iterator na maksimalni element.
// Elementi se porede koristeci operator `<`.
template <typename ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
{
    // Prazna kolekcija.
    if (first == last) return last;

    // Pretpostavimo da je prvi najveci.
    ForwardIterator largest = first;
    ++first;
    for (; first != last; ++first)
    {
        if (*largest < *first)
        {
            largest = first;
        }
    }
    return largest;
}

// Funkcija `accumulate` vrsi akumuliranje vrednosti kroz kolekciju podataka
// koristeci operator '+' i koristeci neutral `init`.
template <typename ForwardIterator, typename T>
T accumulate(ForwardIterator first, ForwardIterator last, T init)
{
    for (; first != last; ++first)
    {
        init = std::move(init) + *first;
    }
    return init;
}

} // namespace matf

int main()
{
    // Testiramo maksimum
    TITLED_BAR("Testiranje funkcije za trazenje maksimuma:");
    std::cout << "matf::max(2, 3) = " << matf::max(2, 3) << std::endl;    
    std::cout << "matf::max(2.3, 2.4) = " << matf::max(2.3, 2.4) << std::endl;    
    std::cout << "std::max(2, 3) = " << std::max(2, 3) << std::endl;

    TITLED_BAR("matf::iota");
    // Inicijalizacija vektora rednim brojevima pocevsi od 1.
    // Primetite da smo pri alokaciji vektora prosledili broj 5,
    // cime smo unapred konstruisali pet "podrazumevanih" `int` vrednosti u vektoru
    // (te vrednosti su, naravno, celobrojne nule).
    std::vector<int> v(5u);

    matf::iota(v.begin(), v.end(), 1);
    for (const auto& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    TITLED_BAR("matf::max_element");
    std::cout << "Najveci element: " << *matf::max_element(v.cbegin(), v.cend()) << std::endl;

    TITLED_BAR("matf::accumulate");
    std::cout << "Suma std::accumulate: " << std::accumulate(v.begin(), v.end(), 0) << std::endl;
    std::cout << "Suma matf::accumulate: " << matf::accumulate(v.begin(), v.end(), 0) << std::endl;

    TITLED_BAR("matf::accumulate sa tackama");
    std::cout << "Inicijalizacija vektora" << std::endl;
    std::vector<Point> xs;
    // Uocite razliku pri konstrukciji objekata i dodavanju u vektor
    // ako se koriste `push_back` i `emplace_back`.
    xs.reserve(3);
    xs.push_back(Point(1, 1));
    //xs.emplace_back(1, 1);
    xs.emplace_back(2, 2);
    xs.emplace_back(3, 4);

    const Point neutral(0, 0);

    std::cout << "\n----accumulate----" << std::endl;
    // Uocite redosled pozivanja konstruktora i move operatora.
    // Zakomentarisite move konstruktor i move operator dodele pa analizirajte
    // ponasanje ovog dela koda ponovo.
    // Iako se unutar matf::accumulate vrsi izmena neutrala, primetite da se on
    // kopira pri pozivu funkcije, i da je nakon funkcije i dalje vrednost u redu,
    // te ga zbog toga deklarisemo kao konstantnog.
    const auto p = matf::accumulate(xs.begin(), xs.end(), neutral);
    std::cout << "neutral: " << neutral.x << ", " << neutral.y << std::endl;
    std::cout << "suma: " << p.x << ", " << p.y << std::endl;

    return 0;
}
