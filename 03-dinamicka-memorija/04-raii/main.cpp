// Primer ispravne implementacije rada sa resursima.
// Resurs moze biti datoteka, konekcija ka bazi podataka, dinamicka memorija, i dr.

// Nacin implementacije u programskom jeziku C
#include <cstdio>

int foo_c()
{
    // Zbog inicijalizacije i deinicijalizacije resursa je
    // prilikom pisanja C programa nastala praksa da
    // bi metod trebalo da ima samo jedan izlaz, tj. jednu return naredbu
    //
    // Za C++ ovo ne moze biti praksa, jer i pored jedne naredbe return, 
    // izlaz iz metoda moze da se pojavi bilo gde, tj.
    // izuzetak moze biti ispaljen bilo gde u kodu.
    //
    // Tako da je ideja inicijalizacije na pocetku metoda
    // i deinicijalizacija na kraju nesto sto je obeshrabreno.

    int return_value = 0;

    // Inicijalizacija resursa se vrsi na pocetku funkcije
    FILE * file = fopen("data.txt", "r");
    if (file != NULL)
    {
        int number;
        while (fscanf(file, "%d", &number) != EOF)
        {
            if (number < 0)
            {
                return_value = 1;
                break;
            }
            printf("%d ", number);
        }
        printf("\n");
    }
    else
    {
        return_value = 1;
    }

    // Deinicijalizacija resursa se vrsi na kraju funkcije
    fclose(file);

    return return_value;
}

// Nacin implementacije u programskom jeziku C++
#include <iostream>
#include <fstream>
#include <string>

// Resource Acquisition Is Initialization (skr. RAII)
// predstavlja tehniku programiranja u jeziku C++
// kojom se zivotni ciklus nekog resursa
// vezuje za zivotni ciklus odgovarajuceg objekta.
// Drugim recima, resurs se dobija kada se objekat konstruise,
// dok se resurs oslobadja kada se objekat unistava.

// Koristiti konstruktore za inicijalizaciju,
// odnosno, destruktore za deinicijalizaciju resursa.
class[[nodiscard]] my_file
{
public:
    my_file()
    {
        // Inicijalizacija resursa se vrsi u konstruktoru
        m_file = std::ifstream("data.txt");
        std::cout << "Datoteka je " << (m_file.is_open() ? "uspesno" : "neuspesno") << " otvorena" << std::endl;
    }

    ~my_file()
    {
        // Deinicijalizacija resursa se vrsi u destruktoru
        m_file.close();
        std::cout << "Datoteka je uspesno zatvorena" << std::endl;
    }

    std::ifstream m_file;
};

void foo_cpp()
{
    my_file file;

    int number;
    while (file.m_file >> number)
    {
        if (number < 0)
        {
            std::cout << std::endl;
            // Doslo je do greske, prijavi (ispali) izuzetak u izvrsavanju programa.
            // Izuzetak moze biti (skoro) bilo koja vrednost koja moze da se kopira.
            throw std::string("Neki izuzetak");
        }
        std::cout << number << " ";
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "Testiramo nacin implementacije u programskom jeziku C..." << std::endl;
    int return_value = foo_c();
    if (return_value == 0)
    {
        std::cout << "C funkcija se zavrsila uspesno" << std::endl;
    }
    else
    {
        std::cout << "C funkcija se zavrsila neuspesno" << std::endl;
    }

    std::cout << std::endl << "Testiramo nacin implementacije u programskom jeziku C++..." << std::endl;
    // Pokusavamo da izvrsavamo problematicnu funkciju
    try
    {
        foo_cpp();
        std::cout << "C++ funkcija se zavrsila uspesno" << std::endl;
    }
    // Hvatamo izuzetak koji je ispaljen na osnovu njegovog tipa.
    // S obzirom da se izuzetak kopira prilikom ispaljivanja,
    // ako ga ne uhvatimo po referenci, imacemo duplo kopiranje.
    catch (const std::string & error_str)
    {
        std::cout << "C++ funkcija se zavrsila neuspesno: " << error_str << std::endl;
    }
}