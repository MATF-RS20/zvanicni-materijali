#ifndef MATF_LIST_HPP
#define MATF_LIST_HPP

#include <memory>
#include <iostream>

namespace matf
{
    class list 
    {
    public:
        // Kada napisemo "= default" nakon metoda,
        // onda ce kompilator definisati podrazumevano telo.
        // Na primer, za podrazumevani konstruktor, telo je prazno,
        // te nema potrebe za implementacijom u list.cpp datoteci.
        list() = default;

        // Kad god se napravi destruktor, obavezno je napraviti
        // i konstruktor kopije i operator dodele (rule of 3),
        // ili ih eksplicitno izbrisati (navodjenjem "= delete" nakon metoda),
        // a pozeljno je napraviti i konstruktor operator dodele 
        // sa semantikom pomeranja (rule of 5).
        ~list();

        // Kljucnom reci noexcept navodimo da metod nece izbacivati izuzetke.
        // Ukoliko noexcept metod ipak izbaci izuzetak,
        // i taj izuzetak nije uhvacen i obradjen unutar funkcije,
        // C++ program to smatra za gresku od koje nema oporavka,
        // te ce pozvati std::terminate() i zavrsice se.
        // Za neke metode se smatra da bi trebalo da budu noexcept, 
        // kao sto su metodi sa semantikom pomeranja ispod.

        // Konstruktor kopije
        list(const list& other);

        // Konstruktor sa semantikom pomeranja
        list(list&& other) noexcept;

        // Operator dodele koji pravi kopiju podataka
        list& operator= (const list& other);

        // Operator dodele sa semantikom pomeranja
        list& operator= (list&& other) noexcept;

        // Operacije za rad sa listom
        void push_front(const int value);
        void push_back(const int value);

        void pop_front();

        size_t size() const;

        // Operator indeksiranja kojim samo dohvatamo element
        int operator[] (const size_t index) const;
        // Operator indeksiranja kojim dohvatamo element za menjanje
        int& operator[] (const size_t index);

    private:
        // Struktura koja predstavlja jedan element jednostruko-povezane liste.
        // Deklarisana je kao privatna unutrasnja struktura klase list,
        // da bi se koristila samo unutar klase list.
        struct element 
        {
            explicit element(int value = 0, std::unique_ptr<element>&& next = nullptr);

            int value;
            std::unique_ptr<element> next;
        };

        element* at(const size_t index) const;

        std::unique_ptr<element> m_start = nullptr;
        size_t m_size = 0;
    };
}

std::ostream& operator<<(std::ostream& out, const matf::list & l);

#endif /* !MATF_LIST_HPP */
