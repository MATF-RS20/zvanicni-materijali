// Zadatak: Napisati funkciju split koja prihvata nisku kao parametar,
// i konstruise vektor reci koje se nalaze u datoj niski. 

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

std::vector<std::string> split(const std::string & str)
{
    std::vector<std::string> result;

    auto word_begin = str.cbegin();

    // Idemo dok ne stignemo do kraja stringa
    while (word_begin != str.cend()) 
    {
        // Preskacemo razmake sa pocetka
        word_begin = std::find_if_not(word_begin, str.cend(), isspace);

        // Trazimo kraj reci
        const auto word_end = std::find_if(word_begin, str.cend(), isspace);

        // Kopiramo karaktere u izlazni vektor
        if (word_begin != str.cend()) 
        {
            result.emplace_back(word_begin, word_end);
        }

        // Zavrsavamo petlju nastavljajuci od kraja prethodne reci
        word_begin = word_end;
    }

    return result;
}

int main(int argc, const char *argv[])
{
    const auto message = split("   Splitting        atoms     or      strings              ");

    std::copy(message.cbegin(), message.cend(), 
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}

