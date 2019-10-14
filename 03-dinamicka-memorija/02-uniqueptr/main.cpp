// Rad sa std::unique_ptr "pametnim" pokazivacem
#include <memory>
#include <string>
#include <iostream>

struct example_object
{
    example_object(const int number, const std::string & text)
        : m_number(number)
        , m_text(text)
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

void testiraj_promenu_vlasnistva(const std::unique_ptr<example_object> p)
{
    std::cout << "U funkciji testiraj_promenu_vlasnistva: " << p->m_number << " - " << p->m_text << std::endl;
}

void testiraj_prosledjivanje_pokazivaca_po_referenci(const std::unique_ptr<example_object> & p)
{
    std::cout << "U funkciji testiraj_prosledjivanje_pokazivaca_po_referenci: " << p->m_number << " - " << p->m_text << std::endl;
}

int main()
{
    // Klasa std::unique_ptr sluzi da zameni koriscenje "cistih" pokazivaca
    // u situacijama kada najvise jedan pokazivac moze da sadrzi adresu na neki objekat.
    auto p1 = std::make_unique<example_object>(10, "Ovaj objekat sadrzi broj 10");
    // Kopiranje nije dozvoljeno:
    // const auto p2(p1); // Konstruktor kopije je obrisan (= delete)
    // const auto p3 = p2;  // Operator dodele sa semantikom kopiranja je obrisan (= delete)

    std::cout << "p1: " << p1->m_number << " - " << p1->m_text << std::endl;

    std::cout << std::endl;
    std::cout << "Testiramo da li je vlasnistvo prebaceno sa p1 na p2..." << std::endl;

    auto p2(std::move(p1));

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
    // testiraj_promenu_vlasnistva(p3);
    // Ali zato naredni poziv uspeva, sa napomenom da ce funkcija preuzeti vlasnistvo objekta
    testiraj_promenu_vlasnistva(std::move(p3));

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
    testiraj_prosledjivanje_pokazivaca_po_referenci(p3);

    if (p3 != nullptr)
    {
        std::cout << "p3: " << p3->m_number << " - " << p3->m_text << std::endl;
    }
    else
    {
        std::cout << "p3 je izgubio vlasnistvo nad dinamickim objektom" << std::endl;
    }

    return 0;
}