#include <iostream>
#include <string>

// Ponekad implementacija metoda koji dolaze u parovima
// i zavise jedan od drugog mogu da nam dosade.
// Na primer, zasto ne napravimo klasu koja ce nam
// dozvoljavati da definisemo samo operator ==,
// a != da bude automatski implementiran (ili obrnuto)?

template <typename T>
class equality_testable 
{
public:
    bool operator==(const T & other) const
    {
        // Dva objekta su jednaka ako nisu razlicita
        return !(static_cast<const T&>(*this) != other);
    }

    bool operator!=(const T & other) const
    {
        // Dva objekta su razlicita ako nisu jednaka
        return !(static_cast<const T&>(*this) == other);
    }
};

// Pravimo klasu koja ce testirati implementirane operatore
class test: public equality_testable<test> 
{
public:
    test(const std::string & data)
        : m_data(data)
    {
    }

    // Ovde definisemo samo operator==,
    // a operator!= ce biti koriscen iz bazne klase.
    bool operator==(const test & other) const
    {
        return other.m_data == m_data;
    }

private:
    std::string m_data;
};

int main()
{
    const test t1("data1"), t2("data2");

    // Sada sve radi kako bi trebalo
    std::cout << (t1 == t1) << std::endl;
    std::cout << (t1 != t1) << std::endl;
    std::cout << (t1 == t2) << std::endl;
    std::cout << (t1 != t2) << std::endl;

    return 0;
}
