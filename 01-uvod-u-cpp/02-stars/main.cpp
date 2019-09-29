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

    // Read line by line
    while (std::cin) {
        messages.push_back(std::string());

        // Funkcija dostupna u <string> zaglavlju.
        // istream& getline (istream& is, string& str, char delim);
        // istream& getline (istream& is, string& str);
        getline(std::cin, messages.back());

        // Trazimo maximum
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
        // Ignorisemo prazne linije
        if (!line.empty()) {
            std::cout
                << "* " << line
                << std::string(maximum_length - line.size(), ' ')
                << " *" << std::endl;
        }
    }

    // Ispisujemo donji separator.
    std::cout << bar << std::endl;

    return 0;
}
