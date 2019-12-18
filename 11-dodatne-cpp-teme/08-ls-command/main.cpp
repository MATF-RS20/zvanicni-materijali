// Primer koji ilustruje neke elemente biblioteke `std::filesystem`:
// https://en.cppreference.com/w/cpp/filesystem

#include <iostream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <vector>
#include <filesystem>

using namespace std;
using namespace filesystem;

// Klasa `std::filesystem::path` predstavlja putanju na disku.
// Klasa `std::filesystem::file_status` cuva informacije o tipu i dozvolama.
// Tip `std::uintmax_t` se koristi za odredjivanje velicine datoteke na disku.
using file_information = tuple<path, file_status, uintmax_t>;

// Pomocna funkcija koja vraca torku informacija iz datoteke na disku.
// Klasa `std::filesystem::directory_entry` predstavlja jednu stavku u direktorijumu.
static file_information file_info(const directory_entry & entry)
{
    // Funkcija `std::filesystem::status` se koristi za
    // odredjujivanje statusa datoteke (tj. `std::filesystem::file_status`)
    const auto fs = status(entry);
    // Funkcija `std::filesystem::file_size` odredjuje velicinu datoteke na disku.
    return {entry.path(),
            fs,
            is_regular_file(fs) ? file_size(entry.path()) : 0u};
}

// Pomocna funkcija koja izracunava tip datoteke na disku.
static char type_char(const file_status & fs)
{
    // Funkcije `std::filesystem::is_*` koje se koriste u kodu ispod
    // proveravaju tip datoteke na disku
    // na osnovu prosledjenog `std::filesystem::file_status` objekta.
    if (is_directory(fs)) { return 'd'; }
    else if (is_symlink(fs)) { return 'l'; }
    else if (is_character_file(fs)) { return 'c'; }
    else if (is_block_file(fs)) { return 'b'; }
    else if (is_fifo(fs)) { return 'p'; }
    else if (is_socket(fs)) { return 's'; }
    else if (is_other(fs)) { return 'o'; }
    else if (is_regular_file(fs)) { return 'f'; }
    return '?';
}

// Pomocna funkcija koja izracunava nisku sa dozvolama.
// Dozvole su implementirane kroz enumerator `std::filesystem::perms`.
static string rwx(const perms p)
{
    const auto check = [p](perms bit, char c) {
        return (p & bit) == perms::none ? '-' : c;
    };
    return {check(perms::owner_read, 'r'),
            check(perms::owner_write, 'w'),
            check(perms::owner_exec, 'x'),
            check(perms::group_read, 'r'),
            check(perms::group_write, 'w'),
            check(perms::group_exec, 'x'),
            check(perms::others_read, 'r'),
            check(perms::others_write, 'w'),
            check(perms::others_exec, 'x')};
}

// Pomocna funkcija koja vraca citljivu velicinu datoteke
static string size_string(uintmax_t size)
{
    // Klasa `std::stringstream` predstavlja tok za citanje/pisanje niski
    stringstream ss;
    // Celobrojni literali predefinisu `operator'`
    // koji se moze koristi za povecanje citljivosti.
    if (size >= 1'000'000'000)
    {
        ss << (size / 1'000'000'000) << 'G';
    }
    else if (size >= 1'000'000)
    {
        ss << (size / 1'000'000) << 'M';
    }
    else if (size >= 1'000)
    {
        ss << (size / 1'000) << 'K';
    }
    else
    {
        ss << size << 'B';
    }
    // Metod `std::stringstream::str` dohvata `std::string`
    // iz toka za citanje/pisanje niski
    return ss.str();
}

int main(int argc, char *argv[])
{
    const path dir = argc > 1 ? argv[1] : ".";
    if (!exists(dir))
    {
        cout << "Path " << dir << " does not exist.\n";
        return 1;
    }

    vector<file_information> items;
    // Klasom `std::filesystem::directory_iterator`
    // mozemo iterirati kroz sadrzaj nekog direktorijuma.
    // Postoji i klasa `std::filesystem::recursive_directory_iterator`
    // kojom mozemo iterirati rekurzivno kroz sadrzaj nekog direktorijuma.
    transform(directory_iterator{dir}, {}, back_inserter(items), file_info);

    for (const auto &[path, status, size] : items)
    {
        cout << type_char(status)
             << rwx(status.permissions()) << " "
             << setw(4) << right << size_string(size)
             << " " << path.filename()
             << endl;
    }

    return 0;
}