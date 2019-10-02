#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    // Niz linija koje ce biti unete sa standardnog ulaza.
    std::vector<std::string> messages;

    // Duzina najduze linije za unte poruke.
    size_t maximum_length = 0;

    // Prva verzija - laksa varijanta, ali postoji mali problem.
    // Kada se unese EOF, indikator da je unet se aktivira tek
    // nakon naredbe `getline(std::cin, messages.back())` tako da
    // petlja ima iteraciju vise.
    /*
    while (std::cin) {
        messages.push_back(std::string());

        // Funkcija dostupna u <string> zaglavlju.
        // istream& getline (istream& is, string& str, char delim);
        // istream& getline (istream& is, string& str);
        getline(std::cin, messages.back());

        // Trazimo maksimum.
        const size_t line_length = messages.back().size();
        maximum_length = line_length > maximum_length ? line_length : maximum_length;
    }
    */

    // Kako bi izbegli problem oko EOF-a, mozemo da drugacije postavimo uslov,
    // odnosno da pokusamo citanje unutar uslova while petlje. Funkcija `getline`
    // vraca referencu na ulazni tok koji joj je prosledjen, sto je u ovom slucaju
    // std::cin, tako da se nakon citanja (i eventualnog pojavljivanja EOF-a) vrsi
    // provera uslova while petlje.
    std::string line;
    while (getline(std::cin, line)) {
        // Ako smo usli u petlju, dodajemo unetu liniju u poruke.
        messages.push_back(line);

        // Praznimo pomocni string (efikasna operacija).
        line.clear();

        // Trazimo maksimum.
        const size_t line_length = messages.back().size();
        maximum_length = line_length > maximum_length ? line_length : maximum_length;
    }

    // *********************************************************** //
    // Za one koji zele da rade unapred:                           //
    // Da li mozete pronaci duzine najduze linije bez for petlje?  //
    // *********************************************************** //

    // Separator sa zvezdicama ima duzinu najduze linije + 4
    // usled toga sto poruku "hello" menjamo sa "* hello *".
    const std::string bar(maximum_length + 4, '*');

    // Ispisujemo gornji separator.
    std::cout << bar << std::endl;
    
    // Ispisujemo poruke okruzene zvezdicama.
    for (const auto& line: messages) {
        std::cout
            << "* " << line
            << std::string(maximum_length - line.size(), ' ')
            << " *" << std::endl;
    }

    // Ispisujemo donji separator.
    std::cout << bar << std::endl;

    return 0;
}
