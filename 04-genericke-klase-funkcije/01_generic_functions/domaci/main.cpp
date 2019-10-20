#include <iostream>
#include <vector>
#include <numeric>

namespace matf {

// Implementirati funkciju koja prikazuje kolekciju podataka
// sa imenom `name` tako sto na `std::cout` vrsi njen ispis.
// std::vector<int> xs{100, 200, 300, 400};
// Na primer: show_collection("xs", xs.cbegin(), xs.cend())
// xs: 100 200 300 400
template <typename It>
void show_collection(const std::string& name, It first, It last)
{

}

// Implementirati funkciju koja vraca iterator na prvi element u kolekciji
// koji je jednak argumentu `value`. Ako funkcija ne pronadje takav element,
// vratiti iterator na kraj kolekcije.
template <typename ForwardIterator, typename T>
ForwardIterator find(ForwardIterator first, ForwardIterator last, const T& value)
{
}

// Implementirati funkciju koja vraca iterator na prvi element u kolekciji
// koji zadovoljava predikat `p`. Ako funkcija ne pronadje takav element,
// vratiti iterator na kraj kolekcije.
template <typename ForwardIterator, typename UnaryPredicate>
ForwardIterator find_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p)
{
}

// Implementirati funkciju koja pocevsi od iteratora `first` pa do iteratora
// `last` postavlja vrednost `value`.
template <typename ForwardIterator, typename T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
}

// Napisati funkciju koja prosledjenu vrednost `v` odseca na interval
// [low, high] tako sto:
// - v < low    => v = low
// - v > high   => v = high
// - inace      => v
template <typename T>
const T& clamp(const T& v, const T& low, const T& high)
{
    return (v < low) ? low : (high < v) ? high : v;
}
// Nakon sto resite, odgovorite na sledece:
// Da li je bolje (1) ili (2)? Zasto?
// (1) v < low i high < v
// (2) v < low i v > high

} // namespace matf

bool odd(int x)
{
    return x % 2 != 0;
}

int main()
{
    std::vector<int> xs(10);
    std::iota(xs.begin(), xs.end(), 100);

    matf::show_collection("xs", xs.cbegin(), xs.cend());

    // find
    auto pos = matf::find(xs.cbegin(), xs.cend(), 105);
    if (pos != xs.cend()) {
        std::cout << "Pronadjen element " << *pos << std::endl;
    } else {
        std::cout << "Nije uspela pretraga." << std::endl;
    }

    // find if
    pos = matf::find_if(xs.cbegin(), xs.cend(), odd);
    if (pos != xs.cend()) {
        std::cout << "Prvi neparni broj: " << *pos << std::endl;
    } else {
        std::cout << "Nije uspela pretraga." << std::endl;
    }

    // fill
    matf::fill(xs.begin(), xs.end(), 100);
    matf::show_collection("xs", xs.cbegin(), xs.cend());

    // clamp
    float value = 1.3;
    // Dedukcija sablona ne uspeva ako se ne navede <float> za
    // poziv matf::clamp(value, 0, 1) jer ne postoji funkcija
    // matf::clamp(float, int, int). Kada navedemo <float>
    // pri pozivu, vrednosti 0 i 1 se implicitno kastuju u float
    // te se pronalazi funkcija matf::clamp(float, float, float).
    //float result = matf::clamp<float>(value, 0, 1);
    // Ili alternativa:
    float result = matf::clamp(value, 0.0f, 1.0f);
    std::cout << "clamp(1.3, 0, 1) = " << result << std::endl;

    return 0;
}
