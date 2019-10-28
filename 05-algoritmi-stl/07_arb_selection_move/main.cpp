// Zadatak: Napisati sablonsku funkciju move_selection koja prihvata 
// iteratore na pocetak i kraj dela kolekcije, iterator na odredisnu lokaciju
// i predikat kojim testiramo vrednosti. 
// Funkcija pomera sve elemente koji zadovoljavaju predikat 
// oko mesta na koje pokazuje iterator na odredisnu lokaciju.

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <functional>

// Stavka je selektovana ako pocinje zvezdom
bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

template <typename Pred, typename Value>
bool not_predicate(Pred predicate, const Value & val)
{
    return !predicate(val);
}

template <typename It, typename Pred>
void move_selection(It first, It last, It destination, Pred predicate)
{
    // Problem mozemo da razdvojimo na dva dela:

    // 1. Particionisemo deo kolekcije od pocetka do destination iteratora,
    //    u ovom delu zelimo da pomerimo selektovane elemente na kraj
    std::stable_partition(first, destination,
                          // Ove nam je potrebna funkcija koja vraca `true` kada `predicate` vrati false i obrnuto.
                          // Jedan nacin je da napisemo sablon koji to radi (`not_predicate`), 
                          // pa da "vezemo" argument koji ce nam proslediti stable_partition,
                          // sto se moze izvesti pozivanjem funkcije `std::bind`, 
                          // pri cemu `std::placeholders::_1` predstavlja taj argument koji ce biti prosledjen.
                          // Medjutim, dodatni problem je sto moramo da eksplicitno navedemo tipove za dati sablon.
                          // Tip za predikat vec imamo, ali tip vrednosti kolekcije nemamo.
                          // Na srecu, dostupan nam je operator decltype 
                          // koji da prosledjenu vrednost dedukuje o kojem tipu je rec.
                          std::bind(not_predicate<Pred, decltype(*first)>, predicate, std::placeholders::_1)
                          // Kada budemo ucili lambda izraze, videcemo da su one mnogo pogodnije za rad (od C++11).
                          // Na primer, ovde je mnogo lakse proslediti naredni lambda izraz
                          // koji radi istu stvar, ali bez definisanja `not_predicate` i "mucenja" oko tipova.
                          // [predicate] (const auto &item) { return !predicate(item); }
    );

    // 2. Particionisemo deo kolekcije od destination iteratora do kraja,
    //    ovde zelimo da pomerimo selektovane elemente na pocetak
    std::stable_partition(destination, last,
                          predicate);
}

int main(int argc, char *argv[])
{
    std::vector<std::string> items {
            "aardvark",
            "compunctious",
            "**congratulations**",
            "contrafribblarity",
            "contrary",
            "dictionary",
            "**interphrastical**",
            "**patronise**",
            "**pericombobulation**",
            "phrasmotic",
            "**syllables**"
        };

    move_selection(std::begin(items), std::end(items), std::begin(items) + 5,
                   is_selected);

    std::copy(std::begin(items), std::end(items),
              std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}
