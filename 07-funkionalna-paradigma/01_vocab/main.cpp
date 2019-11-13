#include <string>
#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>

// Metod koji menja originalni string tako sto 
// sva slova pretvara u mala.
void string_to_lower(std::string & str)
{
    std::transform(str.begin(), str.end(), str.begin(), tolower);
}

// Funkcionalni objekti implementiraju "operator pozivanja",
// tako da kada se kreira objekat ove klase,
// moguce ga je "pozivati".
// Argumenti ovog operatora su argumenti koje prosledjujemo pri "pozivu".
class compare_ignorecase 
{
public:
    bool operator() (std::string left, std::string right) const
    {
        // Radi demonstracije, necemo pokazivati kako se ovo radi 
        // preko vec postojecih metoda za poredjenje niski
        // poput strcasecmp ili (boost) lexicographical_compare.
        // Radicemo tako sto cemo prvo konvertovati left i right
        // da se sastoje samo od malih slova. 
        // Da bismo to uradili, ne smeju biti reference, a ni konstantni.
        string_to_lower(left);
        string_to_lower(right);

        return left < right;
    }
};

int main()
{
    // Kreiramo recnik, pri cemu 
    // kao operaciju poredjenja koristimo funkcionalni objekat.
    std::map<std::string, std::string, compare_ignorecase> words;

    // Ucitavamo reci iz datoteke
    std::ifstream in("data/words");

    std::string word;
    std::string definition;

    while (in >> word) {
        std::getline(in, definition);
        words[word] = definition;
    }

    // Ispisujemo sve reci 
    // koje pocinju prefiksom koji korisnik zada
    std::string query;
    std::cout << "Unesite rec za pretragu: ";

    while (std::cin >> query) 
    {
        // Trazimo iterator na prvu rec 
        // koja je veca ili jednaka onoj koju je korisnik zahtevao
        auto lower = words.lower_bound(query);

        // Trazimo iterator na prvu rec 
        // koja ne pocinje onim sto je korisnik zahtevao.
        // To radimo tako sto "uvecamo" poslednji karakter u upitu,
        // pa onda trazimo prvu rec sa tim prefiksom.
        // query[query.size() - 1]++;
        (*query.rbegin())++;
        auto upper = words.lower_bound(query);

        for (; lower != upper; ++lower) 
        {
            std::cout << lower->first << " -> " << lower->second << std::endl;
        }

        std::cout << "Unesite rec za pretragu: ";
    }

    return 0;
}
