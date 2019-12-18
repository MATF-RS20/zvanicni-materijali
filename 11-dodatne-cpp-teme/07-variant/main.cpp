#include <iostream>
#include <variant>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

// C-ovski nacin za skladistenje vrednosti razlicitog tipa - koriscenjem unija
union U
{
    int a;
    char *b;
    float c;
};

void func(U u)
{
    // Sta ako unija nije inicijalizovana?
    cout << u.b << endl;
}

// C++ ima korisnu sablonsku klasu `std::variant`.
// U ovom primeru kreiramo dve klase: `cat` i `dog`.
class cat
{
    string name;
public:
    explicit cat(string n)
        : name{std::move(n)}
    {}

    void meow() const
    {
        cout << name << " says Meow!" << endl;
    }
};

class dog
{
    string name;
public:
    explicit dog(string n)
        : name{std::move(n)}
    {}

    void woof() const
    {
        cout << name << " says Woof!" << endl;
    }
};

// Zatim koristimo `std::variant`
// radi kreiranja novog tipa `animal`
// koji moze biti `cat` ili `dog`.
using animal = variant<dog, cat>;

// Pomocni funkcionalni objekat kojim se `animal` oglasava
struct animal_voice
{
    void operator()(const dog &d) const
    {
        d.woof();
    }

    void operator()(const cat &c) const
    {
        c.meow();
    }
};

int main()
{
    list<animal> l {cat{"Garfield"}, dog{"Shirou"}, dog{"Benjamin"}};

    for (const animal &a : l)
    {
//        Mozemo koristiti metod index() da odredimo koji je tip,
//        a zatim da iskoristimo funkciju get() da dohvatimo konkretan tip
//
//        switch (a.index())
//        {
//            case 0:
//                get<dog>(a).woof();
//                break;
//            case 1:
//                get<cat>(a).meow();
//                break;
//        }

        // Elegantniji nacin je da koristimo funkciju `std::visit`,
        // koja ce koristiti napisani funkcionalni objekat.
        // Koriscenjem `std::variant` se neverovatno jednostavno implementira
        // obrazac za projektovanje Posetilac (Visitor).
        visit(animal_voice{}, a); // -> Bice pozvano odgovarajuce preopterecenje
                                     //    operatora funkcionalnog objekta
    }

    return 0;
}