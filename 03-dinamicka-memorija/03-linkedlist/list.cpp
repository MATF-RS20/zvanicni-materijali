#include "list.hpp"

namespace matf {

list::~list()
{
    while (m_start)
    {
        pop_front();
    }
}

list::list(const list& other)
{
    for (auto i = 0u; i < other.m_size; ++i)
    {
        push_back(other[i]);
    }
}

// Ideja ove funkcije je da omoguci sledece (pseudokod):
// list xs([1, 2, 3, 4, 5])
// Odnosno, da se privremena lista [1, 2, 3, 4, 5] ne kopira
// pa potom obrise, vec da se direktno preuzme pri konstrukciji
// nase liste.
list::list(list&& other) noexcept
    // Pozivom std::move "krademo" implementaciju od liste koja se prosledjuje.
    : m_start(std::move(other.m_start))
    // Za primitivne tipove, kao sto je size_t, nema potrebe zvati std::move.
    , m_size(other.m_size)
{
    other.m_size = 0;
}

list& list::operator=(const list& other)
{
    // Ovde demonstriramo tzv. "Copy and Swap" idiom: 
    // Da bi operator dodele bio bezbedan prilikom pojave izuzetaka, 
    // obavezno je implementirati ga na ovaj nacin:

    // 1. Pravi se privremena kopija objekta (poziva se konstruktor kopije)
    auto temp(other);
    // 2. Zamene se sve clanske promenljive u *this i privremenoj kopiji
    std::swap(temp.m_start, m_start);
    std::swap(temp.m_size, m_size);
    // Operator dodele uvek vraca referencu na tekuci objekat,
    // kako bismo mogli ulancavati ovaj operator.
    return *this;
}

list& list::operator=(list&& other) noexcept
{
    // Ideja semantike pomeranja jeste da "krademo" implementaciju iz drugog objekta,
    // cime se taj objekat ostavlja "prazan",
    // odnosno, ne bi ga trebalo koristiti dalje.
    m_start = std::move(other.m_start);
    // Ponovo, ovde ne koristimo std::move jer je tip podatka trivijalan,
    // ali moramo da resetujemo broj elemenata u drugoj listi na 0, 
    // kao u konstruktoru sa semantikom pomeranja.
    m_size = other.m_size;
    other.m_size = 0;
    return *this;
}

void list::push_front(int value)
{
    auto new_element = std::make_unique<element>(value, std::move(m_start));
    m_start = std::move(new_element);
    ++m_size;
}

void list::push_back(int value)
{
    auto new_element = std::make_unique<element>(value);

    if (!m_start) 
    {
        m_start = std::move(new_element);
    }
    else 
    {
        auto e = m_start.get();

        while (e->next) {
            e = e->next.get();
        }

        e->next = std::move(new_element);
    }

    ++m_size;
}

void list::pop_front()
{
    auto old_start = std::move(m_start);
    m_start = std::move(old_start->next);
    m_size--;
}

int list::operator[] (const size_t index) const
{
    return at(index)->value;
}

int& list::operator[] (const size_t index)
{
    return at(index)->value;
}

size_t list::size() const
{
    return m_size;
}

list::element::element(const int value, std::unique_ptr<element>&& next)
    : value(value)
    , next(std::move(next))
{
}

list::element* list::at(const size_t index) const
{
    if (!m_start) 
    {
        return nullptr;
    }

    auto e = m_start.get();

    for (auto i = 0u; i < index; ++i) 
    {
        e = e->next.get();

        if (!e) 
        {
            return nullptr;
        }
    }

    return e;
}

} // namespace matf

std::ostream& operator<<(std::ostream& out, const matf::list& l)
{
    for (auto i = 0u; i < l.size(); ++i)
    {
        out << l[i] << " ";
    }
    return out;
}
