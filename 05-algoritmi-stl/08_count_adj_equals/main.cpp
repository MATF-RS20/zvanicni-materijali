// Zadatak: Napisati sablonsku funkciju count_adj_equals 
// koja vraca broj uzastopnih jednakih elemenata kolekcije.

#include <iostream>
#include <string>
#include <numeric>
#include <vector>

template <typename T>
int equal_to_int(const T& left, const T& right)
{
    return left == right ? 1 : 0;
}

template <typename T>
T plus(const T& left, const T& right)
{
    return left + right;
}

// S obzirom da nam je sablonski tip T kolekcija,
// ako zelimo da "izvucemo" koji je sablonski tip jednog elementa kolekcije,
// to mozemo uraditi tako sto iskoristimo vrednost T::value_type.
// Medjutim, zbog nacina kako sabloni rade,
// potrebno je da taj sablonski parametar takodje imenujemo,
// sto se radi sintaksom: "typename Inner = typename T::value_type"
template <typename T,
          typename Inner = typename T::value_type>
int count_adj_equals(const T& xs)
{
    // Algoritam izracunava "skalarni proizvod" dveju kolekcija.
    // Naravno, definicija "skalarnog proizvoda" u ovom kontekstu
    // moze odgovarati bilo kojim binarnim operacijama `+` i `*` koje mi definisemo.
    // U ovom primeru, operacija `*` je ispitivanje da li su vrednosti jednake (`equal_to_int`)
    // dok je operacija + klasicno sabiranje (`plus`).

    // Primer izvrsavanja za nisku: Hooloovoo

    // Primetimo da ovde poredimo kolekciju (bez posl. elementa) 
    // i istu tu kolekciju samo "pomerenu" za jedno mesto ulevo:
    // Hooloovo|o
    // ooloovoo
    // Algoritam ce za svaka dva karaktera pozivati `equal_to_int`, cime ce dobijati vrednosti:
    // 01001001
    // koje ce se "akumulirati" operacijom `plus`, sto daje vrednost 3.
    return std::inner_product(std::begin(xs), std::end(xs) - 1,
                              std::begin(xs) + 1,
                              0,
                              plus<int>,
                              equal_to_int<Inner>);
}

int main(int argc, char *argv[])
{
    const std::string text = "Hooloovoo";

    std::cerr << text << ": " << count_adj_equals(text) << std::endl;

    const std::vector<double> numbers{ -1.0, 2.36, 65.4, 65.4, 65.4, -1.0, 0.0, 5.4 };

    std::cerr << "numbers : " << count_adj_equals(numbers) << std::endl;

    return 0;
}
