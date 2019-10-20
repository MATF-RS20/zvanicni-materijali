#ifndef LIST_HPP
#define LIST_HPP

#include <memory>
#include <utility>

// Genericke klase nazalost ne mozemo da razvojimo u .hpp i .cpp datoteke
// kao sto smo videli na ranijim casovima.
// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
//
// Jedino sto mozemo uraditi jeste odvojiti implementacije u posebnu datoteku zaglavlja
// koja cesto ima ekstenziju .ipp (ili nekad .tpp),
// a potom tu datoteku ukljuciti na dnu .hpp zaglavlja.
// Napomena: Ovakve datoteke (.ipp/.tpp) se NE KOMPILIRAJU, kao ni ostala zaglavlja!
// https://stackoverflow.com/questions/44774036/why-use-a-tpp-file-when-implementing-templated-functions-and-classes-defined-i

namespace matf {

// Uocite prelepu stvar: osim promene 'int' u 'T', i dodavanje template <typename T>
// prakticno nismo nista promenili u klasi.

template <typename T>
class list {
public:
    list() = default;

    ~list()
    {
        while (m_start)
        {
            pop_front();
        }
    }

    list(const list& other)
    {
        for (auto i = 0u; i < other.m_size; ++i)
        {
            push_back(other[i]);
        }
    }

    list(list&& other) noexcept
        : m_start(std::move(other.m_start))
        , m_size(other.m_size)
    {
        other.m_size = 0;
    }

    list& operator= (const list& other)
    {
        auto temp(other);
        std::swap(temp.m_start, m_start);
        std::swap(temp.m_size, m_size);
        return *this;
    }

    list& operator= (list&& other) noexcept
    {
        m_start = std::move(other.m_start);
        m_size = other.m_size;
        other.m_size = 0;
        return *this;
    }

    void push_front(const T value)
    {
        auto new_element = std::make_unique<element>(value, std::move(m_start));
        m_start = std::move(new_element);
        ++m_size;
    }

    void push_back(const T value)
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

    void pop_front()
    {
        auto old_start = std::move(m_start);
        m_start = std::move(old_start->next);
        m_size--;
    }

    size_t size() const
    {
        return m_size;
    }

    // Operator [] je promenjen da uvek vraca referencu,
    // da bismo izbegli kopiranje potencijalno velikih objekata.
    // Ocigledno, da bismo sprecili menjanje objekta,
    // potrebno je da vratimo konstantnu referencu.
    const T& operator[] (const size_t index) const
    {
        return at(index)->value;
    }
    T& operator[] (const size_t index)
    {
        return at(index)->value;
    }

private:
    struct element
    {
        explicit element(T value = 0, std::unique_ptr<element>&& next = nullptr)
            : value(value)
            , next(std::move(next))
        {}

        T value;
        std::unique_ptr<element> next;
    };

    element* at(const size_t index) const
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

    std::unique_ptr<element> m_start = nullptr;
    size_t m_size = 0;
};

} // namespace matf

template<typename T>
std::ostream& operator<<(std::ostream& out, const matf::list<T> & lst)
{
    for (auto i = 0u; i < lst.size(); ++i)
    {
        out << lst[i] << " ";
    }
    return out;
}

#endif /* ifndef LIST_HPP */
