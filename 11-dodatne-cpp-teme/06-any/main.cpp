#include <iostream>
#include <iomanip>
#include <list>
#include <any>
#include <iterator>

using namespace std;

void print_anything(const std::any &a)
{
    if (!a.has_value())
    {
        cout << "Ne postoji vrednost." << endl;
    }
    else if (a.type() == typeid(string))
    {
        cout << "Prosledili ste nisku: "
             << quoted(any_cast<const string&>(a)) << endl;
    }
    else if (a.type() == typeid(int))
    {
        cout << "Prosledili ste celi broj: "
             << any_cast<const int&>(a) << endl;
    }
    else if (a.type() == typeid(list<int>))
    {
        const auto &l = any_cast<const list<int>&>(a);
        cout << "Prosledili ste listu celih brojeva: ";
        copy(begin(l), end(l), ostream_iterator<int>{cout, ", "});
        cout << endl;
    }
    else
    {
        cout << "Prosledili ste " << a.type().name()
             << ", ali to ne znam kako da obradim :( " << endl;
    }
}

int main()
{
    // "Prazan" objekat, tj. objekat bez vrednosti
    print_anything({});
    // Objekat `std::string` se moze konstruisati
    // navodjenjem `s` nakon doslovne (`const char *`) niske
    print_anything("abc"s);
    // Celi broj
    print_anything(123);
    // Lista celih brojeva.
    // Ovde dolazi do kopiranja liste
    // pri inicijalizaciji `std::any` objekta.
    print_anything(list<int>{1, 2, 3});
    // Lista celih brojeva.
    // Ovde nece doci do kopiranja liste,
    // vec se inicijalizacija `std::any` objekta radi u mestu.
    print_anything(any(in_place_type_t<list<int>>{}, {1, 2, 3}));
    // Broj u pokretnom zarezu
    print_anything(3.1415);

    return 0;
}