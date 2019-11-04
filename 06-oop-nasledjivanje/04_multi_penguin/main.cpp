#include <string>
#include <iostream>

// Zelimo da napravimo klasu ptica koja moze da pliva i da leti.
// Pticu ne zelimo da korisnik moze direktno da instancira.
class bird 
{
protected:
    bird(const std::string & species)
        : m_species(species)
    {}

public:
    std::string species() const
    {
        return m_species;
    }

private:
    std::string m_species;
};

class can_fly 
{
public:
    void fly(const std::string & who)
    {
        std::cout << who << " is in the air" << std::endl;
    }
};

// Pravimo klasu soko. Soko je ptica koja bi trebalo da moze da leti.
class hawk : public bird, public can_fly 
{
public:
    hawk()
        : bird("hawk")
    {}
};

// Pravimo klasu orao. Orao je ptica koja bi trebalo da moze da leti.
class eagle : public bird, public can_fly 
{
public:
    eagle()
        : bird("eagle")
    {}
};

// Sta jos moze da leti, a da nije ptica?
class love: public can_fly 
{};

// Pravimo klasu pingvin. Pingvin je ptica koja ne bi trebalo da moze da leti.
class penguin: public bird 
{
public:
    penguin()
        : bird("penguin")
    {}
};

int main()
{
    hawk h;
    eagle e;
    penguin p;

    h.fly(h.species());
    e.fly(e.species());
    // Kompajler nam sada javlja da pingvini ne mogu da lete
    //p.fly();

    love l;
    l.fly("love");

    return 0;
}
