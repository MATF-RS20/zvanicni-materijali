// Ako zelimo da napravimo klasu za koju zelimo da
// zabranimo kopiranje i operator dodele, 
// dovoljno je da "izbrisemo" njihove implementacije.
// Ako zelimo da napravimo vise takvih klasa,
// ovo ponasanje mozemo da ubacimo u neku od natklasa.

#include <string>
#include <iostream>

// Kompletnu implementaciju ove klase mozete naci u
// boost biblioteci - boost::noncopyable
class non_copyable 
{
public:
    non_copyable(const non_copyable & other) = delete;
    const non_copyable& operator= (const non_copyable & other) = delete;

protected:
    // Ne zelimo da iko moze da napravi direktno instancu nase klase.
    // Moze da pozove konstruktor ili destruktor samo ako je izvedena.
    non_copyable() = default;
    ~non_copyable() = default;
};

// Pravimo klasu koja 'barata' bazom podataka
class database 
{
public:
    database(const std::string & url)
        : m_url(url)
    {
        std::cout << "Povezujem se sa bazom: " << url << std::endl;
    }

    ~database()
    {
        std::cout << "Raskidam konekciju sa bazom: " << m_url << std::endl;
    }

private:
    std::string m_url;
};

// Pravimo klasu koja barata internom bazom.
// Implementacija se oslanja na to da mozemo imati
// samo jednu konekciju ka internoj bazi.
class internal_database : public database, public non_copyable 
{
public:
    internal_database()
        : database("http://localhost/")
    {}
};

int main()
{
    // Kopiranje "obicne" baze radi
    const database db1("http://sql.matf.bg.ac.rs/");
    const auto db1_copy = db1;

    internal_database db2;
    // Linija ispod ne prolazi: 
    // Kompilator javlja poruku da se pokusava kopiranje objekta
    // ciji je konstruktor kopije "izbrisan".
    //internal_database db2_copy = db2;

    return 0;
}
