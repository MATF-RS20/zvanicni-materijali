// Rad sa std::unique_ptr "pametnim" pokazivacem
#include <memory>
#include <string>
#include <iostream>

struct example_object
{
    example_object(const int number, const std::string & text)
        : m_number(number), m_text(text)
    {
        std::cout << "Kreiran je example_object(" << m_number << ", " << m_text << ")" << std::endl;
    }

    ~example_object()
    {
        std::cout << "Obrisan je example_object(" << m_number << ", " << m_text << ")" << std::endl;
    }

    int m_number;
    std::string m_text;
};

void test_ownership_change(const std::unique_ptr<example_object> p)
{
    std::cout << "U funkciji test_ownership_change: " << p->m_number << " - " << p->m_text << std::endl;
}

void test_ref_forward(const std::unique_ptr<example_object> & p)
{
    std::cout << "U funkciji test_ref_forward: " << p->m_number << " - " << p->m_text << std::endl;
}

int main()
{
    // Klasa std::unique_ptr sluzi da zameni koriscenje "cistih" pokazivaca
    // u situacijama kada najvise jedan pokazivac moze da sadrzi adresu na neki objekat,
    // odnosno kada je taj pokazivac glavni i jedini odgovorni vlasnik nad objektom.
    auto p1 = std::make_unique<example_object>(10, "Ovaj objekat sadrzi broj 10");
    // Kopiranje nije dozvoljeno:
    // const auto p2(p1);   // Konstruktor kopije je obrisan (= delete)
    // const auto p3 = p2;  // Operator dodele sa semantikom kopiranja je obrisan (= delete)

    std::cout << "p1: " << p1->m_number << " - " << p1->m_text << std::endl;

    std::cout << std::endl;
    std::cout << "Testiramo da li je vlasnistvo prebaceno sa p1 na p2..." << std::endl;

    auto p2(std::move(p1));
    // U klasu unique_ptr operator bool je definisan tako da vraca tacno ako unique_ptr
    // pokazuje na neki objekat, odnosno get() != nullptr. Kada se promeni vlasnistvo,
    // odnosno pozove move konstruktor za unique_ptr (videcemo sta je move konstruktor
    // u narednom primeru sa listom), stari objekat ce biti azuriran i operator bool
    // ce vracati false jer unique_ptr vise ne pokazuje na objekat (primer ispod).

    if (p1 != nullptr)
    {
        std::cout << "p1: " << p1->m_number << " - " << p1->m_text << std::endl;
    }
    else if (p2 != nullptr)
    {
        std::cout << "p2: " << p2->m_number << " - " << p2->m_text << std::endl;
    }
    else
    {
        std::cout << "Ni p1 ni p2 nemaju vlasnistvo nad dinamickim objektom" << std::endl;
    }

    auto p3 = std::move(p2);
    
    std::cout << std::endl;
    std::cout << "Testiramo prosledjivanje pametnog pokazivaca kao argument funkcije..." << std::endl;
    
    // Naredni poziv proizvodi gresku zato sto se pokusava kopiranje std::unique_ptr objekta
    // test_ownership_change(p3);
    // Ali zato naredni poziv uspeva, sa napomenom da ce funkcija preuzeti vlasnistvo objekta.
    // Posto funkcija preuzima vlasnistvo, nakon njenog rada, objekat se i dealocira jer funkcija
    // zavrsava svoj rad.
    test_ownership_change(std::move(p3));

    if (p3 != nullptr)
    {
        std::cout << "p3: " << p3->m_number << " - " << p3->m_text << std::endl;
    }
    else
    {
        std::cout << "p3 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Testiramo promenu vlasnistva pametnog pokazivaca na neki drugi objekat..." << std::endl;

    p3 = std::make_unique<example_object>(15, "Ovaj objekat sadrzi broj 15");
    std::cout << "p3: " << p3->m_number << " - " << p3->m_text << std::endl;

    std::cout << std::endl;
    std::cout << "Testiramo promenu vlasnistva pametnog pokazivaca u funkciji kada se on prenosi po referenci..." << std::endl;

    // Naravno, pokazivac mozemo preneti i po referenci.
    // U tom slucaju nece doci do prenosa vlasnistva.
    test_ref_forward(p3);

    if (p3 != nullptr)
    {
        std::cout << "p3: " << p3->m_number << " - " << p3->m_text << std::endl;
    }
    else
    {
        std::cout << "p3 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    // Sirovi pokazivac mozemo izvuci koristeci funkciju `get()`.
    // Ovo bi trebalo izbegavati, osim ukoliko nemamo dobar razlog za to - na primer
    // neki stari deo projekta bas zahteva da se prosledi sirovi pokazivac, a nemamo
    // vremena ili dozvolu da menjamo taj deo projekta.
    example_object* raw_ptr = p3.get();

    // unique_ptr (kao i shared_ptr) imamo predefinisane operatore * i -> tako da se
    // unique_ptr objekat sa njima ponasa kao da je sirovi pokazivac, odnosno operator *
    // vrsi dereferensiranje, a -> vrsi pristup objektu na koji pokazuje pametni pokazivac.

    return 0;
}
