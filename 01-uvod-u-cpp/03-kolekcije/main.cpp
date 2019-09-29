#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <forward_list>
#include <list>
#include <deque>

void show_help_and_quit();
void vector_showcase();
void set_showcase();
void map_showcase();
void forward_list_showcase();
void list_showcase();
void deque_showcase();

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        show_help_and_quit();
    }

    const std::string option(argv[1]);

    if (option == "v") vector_showcase();
    else if (option == "s") set_showcase();
    else if (option == "m") map_showcase();
    else if (option == "fl") forward_list_showcase();
    else if (option == "l") list_showcase();
    else if (option == "d") deque_showcase();
    else show_help_and_quit();

    return 0;
}

void show_help_and_quit()
{
    std::cerr << "Program se poziva naredbom: \"./main opcija\"" << std::endl
              << std::endl
              << "Opcija mora biti jedna od: " << std::endl
              << "\tv   = Demonstracija rada kolekcije std::vector<T, ...>" << std::endl
              << "\ts   = Demonstracija rada kolekcije std::set<T, ...>" << std::endl
              << "\tm   = Demonstracija rada kolekcije std::map<Key, T, ...>" << std::endl
              << "\tfl  = Demonstracija rada kolekcije std::forward_list<T, ...>" << std::endl
              << "\tl   = Demonstracija rada kolekcije std::list<T, ...>" << std::endl
              << "\td   = Demonstracija rada kolekcije std::deque<T, ...>" << std::endl;
    exit(EXIT_FAILURE);
}

void vector_showcase()
{
    // Inicijalizacija praznog vektora
    std::vector<int> xs;
    int x;

    std::cout << "Unesite nekoliko celih brojeva: " << std::endl;
    while (std::cin >> x)
    {
        // Dodajemo na kraj vektora svaki uneti broj.
        // Vektor vrsi povremenu realokaciju memorije pri kojoj rezervise
        // vise nego sto mu u tom trenutku potrebno kako bi dodavanje na kraj
        // bilo efikasnije.
        xs.push_back(x);
    }
    
    // Izracunavanje broja elemenata vektora.
    if (! xs.empty())
    {
        // Prikazujemo broj elemenata u vektoru.
        std::cout << "Broj unetih brojeva: " << xs.size() << std::endl;
    }
    else
    {
        std::cout << "Nista nije uneto." << std::endl; 
    }

    std::cout << "Vrsi se dodavanje u vektor koristeci `insert`..." << std::endl;
    // Dodaje se broj na pocetak vektora.
    // Umesto std::cbegin i std::cend moze se koristiti i xs.cbegin() i xs.cend.
    // Preporuceno je koristiti opstiju verziju funkcije std::cbegin() i std::cend()
    // jer rade u vise slucajeva u zavinosti od tipa na kojim se pozivaju (na primer pokazivaci).
    xs.insert(std::cbegin(xs), 17);
    // Dodaje se pet 0 na kraj vektora.
    xs.insert(std::cend(xs), 5, 0);

    // Ispisivanje sadrzaja vektora koristeci kolekcijsku petlju.
    std::cout << "Sadrzaj vektora:" << std::endl;
    for (const auto& x : xs)
    {
        std::cout << "- " << x << std::endl;
    }

    // STL kolekcije su pravljenje sa ciljem da budu izuzetno efikasne,
    // tako da se ne vrsi provera granica prilikom pristupu elementima
    // kolekcije. Ovde treba biti pazljiv i obratiti paznju na granice.
    std::cout << "Prvi element u vektoru: " << xs[0] << std::endl;
    std::cout << "Poslednji element u vektoru: " << xs.back() << std::endl;

    // Dodavanje vrednosti na kraj vektora,
    // pri cemu vrednost konstruisemo u mestu.
    // Vremenska slozenost: Amortizovana konstantna O(1)
    xs.emplace_back(42);
    
    // Kroz vektor mozemo da iteriramo unapred i unazad koristeci iteratore.
    std::cout << "Sadrzaj vektora koristeci cbegin:" << std::endl;
    for (auto iter = std::cbegin(xs); iter != std::cend(xs); iter++)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    // Brisanje poslednjeg elementa.
    // Vremenska slozenost: O(1)
    xs.pop_back();

    // Brisanje elementa na poziciji koja je definisana iteratorom,
    // u ovom slucaju, brisemo element na indeksu 0+3=3.
    // Vremenska slozenost: Linearna
    xs.erase(std::cbegin(xs) + 3);

    std::cout << "Sadrzaj vektora koristeci crbegin:" << std::endl;
    for (auto iter = std::crbegin(xs); iter != std::crend(xs); iter++)
    {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}

/// Tip std::set<T, ...> predstavlja kolekciju koja
/// sadrzi uredjeni skup jedinstvenih vrednosti.
void set_showcase()
{
    // Inicijalizacija skupa pocetnim vrednostima.
    std::set<double> xs{1.0, 2.0, 3.0, -1.0, -4.3, -2.0, 5.0, -6.4};
    double x;

    // Prikazujemo korisniku skup.
    std::cout << "xs: " << std::endl;
    for (const auto& x: xs) std::cout << x << " ";
    std::cout << std::endl;

    // Blok ispod je dodat kako bi se omogucilo da recikliramo imena promenljivih.
    
    // Pretraga u skupu
    {
        std::cout << "\n[Pretraga broja]" << std::endl;
        std::cout << "Unesite broj za pretragu:" << std::endl;
        std::cin >> x;

        // Pronalazak elementa u skupu.
        // Vremenska slozenost: Logaritamska
        const auto iter = xs.find(x);
        if (iter != xs.cend())
        {
            std::cout << "Pronadjen je element " << *iter << std::endl;
        }
        else
        {
            std::cout << "Nije pronadjen element " << x << std::endl;
        }
    }

    // Pretraga prvog elementa strogo veceg od datog.
    // Vremenska slozenost: Logaritamska
    {
        std::cout << "\n[Pretraga prvog veceg]" << std::endl;
        std::cout << "Unesite broj za pretragu:" << std::endl;
        std::cin >> x;

        const auto iter = xs.upper_bound(x);
        if (iter != xs.cend())
        {
            std::cout << "Pronadjen je prvi element " << *iter << " strogo veci od " << x << std::endl;
        }
        else
        {
            std::cout << "Nije pronadjen element strogo veci od " << x << std::endl;
        }
    }

    // Pretraga prvog elementa veceg ili jednakog od datog.
    // Vremenska slozenost: Logaritamska
    {
        std::cout << "\n[Pretraga prvog veceg ili jednakog]" << std::endl;
        std::cout << "Unesite broj za pretragu:" << std::endl;
        std::cin >> x;

        const auto iter = xs.lower_bound(x);
        if (iter != xs.cend())
        {
            std::cout << "Pronadjen je prvi element " << *iter << " veci ili jednak od " << x << std::endl;
        }
        else
        {
            std::cout << "Nije pronadjen element veci ili jednak od " << x << std::endl;
        }
    }

    // Unos vise elemenata u skup
    xs.insert({7.3, 5.0, 7.3, 3.0, 4.0});

    // Prikazujemo korisniku skup.
    std::cout << "\nxs nakon dodavanja: " << std::endl;
    for (const auto& x: xs) std::cout << x << " ";
    std::cout << std::endl;
}

/// Tip std::map<Key, T, ...> predstavlja kolekciju parova (kljuc, vrednost)
/// pri cemu su kljucevi jedinstveni, a kolekcija je uredjena po parovima.
void map_showcase()
{
    std::map<unsigned, std::string> students({
        {20100050u, "Nevena"},
        {20110145u, "Petar"},
        {20100043u, "Ana"}}
    ); 

    // Pristupanje elementima sa datim kljucem.
    // Vremenska slozenost: Logaritamska
    unsigned key_existing = 20110145u;
    unsigned key_not_existing = 20000001u;

    // Koriscenjem prvog pristupa,
    // ukoliko kljuc ne postoji u recniku,
    // bice unet novi par vrednosti u recnik,
    // pri cemu se za vrednost u tom paru uzima podrazumevana vrednost za dati tip (std::string u ovom primeru).
    std::cout << "Student sa indeksom " << key_existing
        << " se zove \"" << students[key_existing] << "\"" << std::endl;
    std::cout << "Student sa indeksom " << key_not_existing
        << " se zove \"" << students[key_not_existing] << "\"" << std::endl;

    // Koriscenjem drugog pristupa,
    // ukoliko kljuc ne postoji u recniku,
    // bice ispaljen std::out_of_range izuzetak.
    std::cout << "Student sa indeksom " << key_existing
        << " se zove \"" << students.at(key_existing) << "\"" << std::endl;

    // Pomeramo kljuc (povecavamo broj) kako jer je prethodna vrednosta
    // dodata u mapu sa students[key_not_existing].
    // Sledeci kod ispaljuje std::out_of_range izuzetak.
    // ++key_not_existing;
    // std::cout << "Student sa indeksom " << key_not_existing
    //          << " se zove \"" << students.at(key_not_existing) << "\"" << std::endl;


    // Unosesenje novog para (kljuc, vrednost)
    // Vremenska slozenost: Logaritamska
    // Konstruisemo par koji zelimo da dodamo.
    const std::pair<unsigned, std::string> new_student(++key_not_existing, "Mihajlo");
    const std::pair<unsigned, std::string> new_student_with_same_key(key_not_existing, "Jelena");

    std::string state_of_input;

    // Povratna vrednost je par (iterator, bool).
    // Ukoliko je unos uspesan, iterator "pokazuje" na uneti par u recniku, a bool vrednost je tacna.
    // Ukoliko unos nije uspesan, iterator "pokazuje" na postojeci par u recniku, a bool vrednost je netacna.
    {
        const auto input = students.insert(new_student);
        const auto iter = input.first;                      // uzimamo prvi element uredjenog para
        const auto successfull = input.second;
        if (successfull)
        {
            state_of_input = "Student je uspesno dodat.";
        }
        else
        {
            state_of_input = "Student nije uspesno dodat.";
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }

    // Primer za unos koji ne uspeva.
    {
        // Mozemo koristiti i otpakivanje koje je dodato u standardu c++17,
        // odnosno mozemo rezultat sa desne strane otpakovati u zasebne promenljive.
        const auto [iter, successfull] = students.insert(new_student_with_same_key);

        if (successfull)
        {
            state_of_input = "Student je uspesno dodat.";
        }
        else
        {
            state_of_input = "Student nije uspesno dodat.";
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }

    // Element za unos mozemo konstruisati i u mestu.
    {
        const auto [iter, successfull] = students.emplace(++key_not_existing, "Nikola");
        if (successfull)
        {
            state_of_input = "Student je uspesno dodat.";
        }
        else
        {
            state_of_input = "Student nije uspesno dodat.";
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }

    // Ako zelimo da novu vrednost upisemo preko stare ako postoji
    // mozemo koristiti `insert_or_assign`.
    {
        std::cout << "Adding: " << new_student_with_same_key.first << std::endl;
        const auto [iter, successfull] = students.insert_or_assign(
            new_student_with_same_key.first,
            new_student_with_same_key.second
        );
        if (successfull)
        {
            state_of_input = "Student je uspesno dodat.";
        }
        else
        {
            state_of_input = "Student je azuriran na ime " + new_student_with_same_key.second;
        }
        std::cout
            << state_of_input << " Recnik sadrzi: ("
            << iter->first << ", " << iter->second << ")" << std::endl;
    }
}

/// Tip std::forward_list<T, ...> predstavlja jednostruko povezanu listu (JPL) vrednosti tipa T.
void forward_list_showcase()
{
    // Inicijalizacija JPL.
    std::forward_list<char> chars{'R', 'a', 'z', 'v', 'o', 'j', ' ', 'S', 'o', 'f', 't', 'v', 'e', 'r', 'a'};

    // Vrlo slicno kao za vektor, provera da li je kolekcija prazna i pristup elementima.
    if (!chars.empty())
    {
        std::cout << "Prvi element je: " << chars.front() << std::endl;
        // Primetite da funkcija `back()` ne postoji, da li mozete da pretpostavite zasto?
        //std::cout << "Poslednji element je: " << chars.back() << std::endl;
    }

    // Pored `cbegin()`, `begin()`, `cend()` i `end()` iteratora postoje i iteratori
    // `cbefore_begin()` i `before_begin()` iteratori koji pokazuju na prvu poziciju
    // pre pocetka liste. Namena ovog iteratora je na primer za funkcije poput:
    // `insert_after()`, `emplace_after()`, `erase_after()`, `splice_after()`. 
    auto iter = chars.before_begin();
    std::cout << "Iterator before_begin "
              << ((++iter == chars.begin()) ? "jeste" : "nije")
              << " ispred begin iteratora" << std::endl;

    // Dodajemo element pre elementa na koji pokazuje prosledjeni iterator,
    // u ovom slucaju, dodajemo '>' na pocetak liste.
    // Vremenska slozenost:
    //  * konstantna - u slucaju unosa jedne vrednosti
    //  * linearna po broju unetih vrednosti
    chars.insert_after(chars.cbefore_begin(), '>');

    // Iterira se kroz listu.
    for (const auto& ch: chars)
    {
        std::cout << ch;
    }
    std::cout << std::endl;

    // Obrtanje liste u mestu.
    // Vremenska slozenost: Linearna
    // Da li znate algoritam vremeneske slozenosti O(n) i memorijske slozenosti O(1)
    // koji vrsi obrtanje jednostruko povezane liste duzine n?
    chars.reverse();
    // Dodajemo tri karaktera `!` na pocetak (obrnute liste).
    chars.insert_after(chars.cbefore_begin(), 3, '!');
    chars.reverse();

    for (const auto& ch: chars)
    {
        std::cout << ch;
    }
    std::cout << std::endl;
}

// Tip std::list<T, ...> predstavlja dvostruko povezanu listu (DPL) vednosti tipa T.
void list_showcase()
{
    // Inicijalizacija DPL pocetnim elementima
    std::list<std::string> keywords{"if", "unsigned", "while", "void"};

    std::cout << "keywords:" << std::endl;
    for (const auto& keyword : keywords)
    {
        std::cout << keyword << " " << std::endl;
    }
    std::cout << std::endl;

    // Provera da li je DPL prazna.
    // Vremenska slozenost: Konstantna
    if (!keywords.empty())
    {
        // Izracunavanje broja elemenata
        // Vremenska slozenost: Konstantna (od C++11)
        std::cout << "Broj elemenata u DPL: " << keywords.size() << std::endl;

        // Pristupanje prvom i poslednjem elementu.
        // Vremenska slozenost: Konstantna
        std::cout << "Prvi element DPL je: \"" << keywords.front() << "\"" << std::endl;
        std::cout << "Poslednji element DPL je: \"" << keywords.back() << "\"" << std::endl;
    }

    // Unosenje jednog ili vise elemenata ispred nekog elementa.
    // Vremenska slozenost: Konstantna (u slucaju unosa jedne vrednosti) ili linearna po broju unetih vrednosti
    std::cout << "Dodaje se 'return' na pocetak." << std::endl;
    keywords.insert(keywords.cbegin(), "return");
    std::cout << "Dodaje se '>' na pocetak 3 puta." << std::endl;
    keywords.insert(keywords.cbegin(), 3, ">");
    std::cout << "Dodaje se '<' na kraj 3 puta." << std::endl;
    keywords.insert(keywords.cend(), 3, "<");

    // Unosenje elementa na pocetak i kraj DPL.
    // Vremenska slozenost: Konstantna
    std::cout << "Dodaje se '{' na pocetak." << std::endl;
    keywords.push_front("{");
    std::cout << "Dodaje se '}' na kraj." << std::endl;
    keywords.push_back("}");

    // Prolazak kroz DPL kolekcijskom petljom
    for (const auto& rec : keywords)
    {
        std::cout << rec << " ";
    }
    std::cout << std::endl;
}

void deque_showcase()
{
    std::deque<unsigned> xs{0, 1, 2, 3, 4, 5, 6, 7};

    for (const auto& x: xs)
    {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    std::cout << "Istraziti mogucnosti kolekcije std::deque<T, ...> za domaci." << std::endl
              << "Napraviti uporednu analizu sa preostalim kolekcijama." << std::endl;
}
