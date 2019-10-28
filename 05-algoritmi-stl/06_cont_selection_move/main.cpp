// Zadatak: Napisati sablonsku funkciju slide_selection koja prihvata
// iteratore na pocetak i kraj dela kolekcije i iterator na poziciju
// ispred koje se pomeraju elementi datog dela kolekcije.
// Funkcija treba da izvrsi dato pomeranje i vrati par iteratora
// koji pokazuju na pomereni deo kolekcije.

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

template <typename It>
std::pair<It, It> slide_selection(It selection_begin, It selection_end, It destination)
{
    if (destination < selection_begin) 
    {
        // Ne moramo koristiti std::make_pair, vec ga mozemo konstruisati inicijalizatorom
        return {
            destination,
            // Algoritam vrsi levu rotaciju dela kolekcije, tako sto zamenjuje elemente iz [first, last)
            // tako da element n_first postaje prvi element u novom delu kolekcije
            // i element n_first - 1 postaje poslednji element u novom delu kolekcije.
            // (Od C++11) Algoritam vraca iterator na novu lokaciju elementa koji pokazuje na first,
            // tj. first + (last - n_first).
            std::rotate(/* first = */ destination, /* n_first * */ selection_begin, /* last = */ selection_end)
        };
    }

    if (selection_end < destination) 
    {
        return {
            std::rotate(selection_begin, selection_end, destination),
            destination
        };
    }

    return { selection_begin, selection_end };
}


int main(int argc, char *argv[])
{
    std::vector<std::string> items {
            "aardvark",
            "compunctious",
            "**congratulations**",  // +2
            "**contrafribblarity**",
            "**contrary**",
            "dictionary",           // +5
            "interphrastical",
            "patronise",            // +7
            "pericombobulation",
            "phrasmotic",
            "syllables"
        };

    const auto [selection_begin, selection_end] =
        slide_selection(std::begin(items) + 2,
                        std::begin(items) + 5,
                        std::begin(items) + 7);

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    std::cout << "---" << std::endl;

    slide_selection(selection_begin,
                    selection_end,
                    std::begin(items));

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
