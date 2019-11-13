#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

class Value 
{
public:
    Value(const int value)
        : value(value)
    {}

    bool odd() const 
    {
        return value % 2 == 1;
    }

    bool even() const 
    {
        return value % 2 == 0;
    }

    bool between(const int min, const int max) const 
    {
        return value >= min && value <= max;
    }

    const int value;
};

int main()
{
    using std::placeholders::_1;

    // Pravimo vektor vrednosti. Od C++11, prilikom poziva konstruktora,
    // preporuceno je koristiti viticaste zagrade umesto obicnih.
    // Pogledati detaljne razlike izmedju ove dve sintakse online.
    // http://programmers.stackexchange.com/questions/133688/is-c11-uniform-initialization-a-replacement-for-the-old-style-syntax
    std::vector<Value> values {1, 2, 3, 4, 5};

    // Algoritam `find_if` vraca iterator na prvi pronadjeni element.
    // Prosledjujemo anonimnu funkciju (anonimni funkcijski objekat).
    // Trazimo prvu parnu vrednost u nizu.
    const auto f1 = std::find_if(values.cbegin(), values.cend(),
            [] (const Value& value) { return value.even(); });
    //      ↑      ↑                  ⬑ telo funkcije
    //      |      └ argumenti
    //      └ glava

    const auto limit = 3;

    // Trazimo prvu vrednost u nizu koja je veca od vrednosti `limit`.
    // Da bi promenljiva `limit` bila vidljiva unutar lambde,
    // moramo da je preciziramo unutar glave. Mozemo da je uhvatimo
    // po vrednosti [limit], po referenci [&limit], mozemo da uhvatimo
    // sve koriscene promenljive po vrednosti [=] ili referenci [&]
    const auto f2 = std::find_if(values.cbegin(), values.cend(),
            [limit] (const Value& value) { return value.value > limit; });
    //      ↑        ↑                     ⬑ telo funkcije
    //      |        └ argumenti
    //      └ glava

    // Takodje možemo da inicijalizujemo proizvoljne clanske promenljive
    // unutar lambde. Ovo je posebno korisno za tipove podataka koji su
    // move-only poput std::unique_ptr
    const auto f3 = std::find_if(values.cbegin(), values.cend(),
            [l = limit + 42] (const Value& value) { return value.value > l; });

    // `std::bind` se moze koristiti za parcijalnu aplikaciju - za
    // definisanje nekih argumenata dok ostale ostavljamo za kasnije.
    // Prvi argument je funkcija kojoj zelimo neke argumente da "vezemo",
    // posle toga definisemo ili 'rupe' ili konkretne vrednosti.
    const auto f4 = std::find_if(values.cbegin(), values.cend(),
            std::bind(&Value::between, _1, 2, 4));
    //                ↑                ↑   ⬑ vezani argumenti
    //                |                └ "rupa"
    //                └ funkcija koju zalimo da parcijalno primenimo
    //
    // bind ce vratiti unarnu funkciju (imamo jednu "rupu", samim tim
    // rezultat ce biti funkcija od jednog argumenta). Kad bude pozvana
    // uz konkretan argument `v`, vratice isti rezultat koji vraca
    // v.between(2, 4)

    if (f1 != values.cend())
    {
        std::cout << "f1: " << (f1->value) << std::endl;
    }
    if (f2 != values.cend())
    {
        std::cout << "f2: " << (f2->value) << std::endl;
    }
    if (f3 != values.cend())
    {
        std::cout << "f3: " << (f3->value) << std::endl;
    }
    if (f4 != values.cend())
    {
        std::cout << "f4: " << (f4->value) << std::endl;
    }
    
    return 0;
}
